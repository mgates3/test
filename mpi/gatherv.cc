#include <stdio.h>
#include <mpi.h>
#include <vector>
#include <numeric>

#include "util.hh"

//------------------------------------------------------------------------------
void test( bool in_place )
{
    int mpi_rank, mpi_size;
    MPI_Comm comm = MPI_COMM_WORLD;
    mpi_call( MPI_Comm_rank( comm, &mpi_rank ) );
    mpi_call( MPI_Comm_size( comm, &mpi_size ) );
    printf( "rank %2d, size %2d\n", mpi_rank, mpi_size );
    MPI_Barrier( comm );  // help order prints (still not guaranteed).

    int maxn = 4;
    int n = mpi_rank % maxn + 1;
    int root = mpi_size - 1;  // last process

    // recv_buf, recv_cnts, recv_offsets needed only on root process.
    int size = 1;
    std::vector<double> recv_buf( size, -1 );
    std::vector<int> recv_cnts( 1, 0 ), recv_offsets( 1, 0 );
    if (mpi_rank == root) {
        recv_cnts.resize( mpi_size );
        for (int r = 0; r < mpi_size; ++r) {
            recv_cnts[ r ] = r % maxn + 1;
        }

        // Do one extra entry to get size.
        recv_offsets.resize( mpi_size + 1 );
        std::partial_sum( &recv_cnts[0], &recv_cnts[ mpi_size ],
                          &recv_offsets[ 1 ] );
        printf( "%2d: recv_cnts      [ %s ]\n",
                mpi_rank, to_string( recv_cnts    ).c_str() );
        printf( "%2d: recv_offsets   [ %s ]\n",
                mpi_rank, to_string( recv_offsets ).c_str() );

        size = recv_offsets[ mpi_size ];
        recv_buf.resize( size, -1 );
    }

    if (mpi_rank == root && in_place) {
        // Everyone including root sends.
        // Initialize in-place.
        std::iota( &recv_buf[ recv_offsets[ mpi_rank   ] ],
                   &recv_buf[ recv_offsets[ mpi_rank+1 ] ],
                   10*mpi_rank );
        printf( "%2d: send to %2d:    [ %s ] (in-place)\n",
                mpi_rank, root, to_string( recv_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Gatherv( MPI_IN_PLACE, n, MPI_DOUBLE,
                         &recv_buf[0], &recv_cnts[0], &recv_offsets[0], MPI_DOUBLE,
                         root, comm ) );
    }
    else {
        // Everyone including root sends.
        std::vector<double> send_buf( n );
        std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );
        printf( "%2d: send %2d to %2d: [ %s ]\n",
                mpi_rank, n, root, to_string( send_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Gatherv( &send_buf[0], n, MPI_DOUBLE,
                         &recv_buf[0], &recv_cnts[0], &recv_offsets[0], MPI_DOUBLE,
                         root, comm ) );
    }

    // Only root receives.
    if (mpi_rank == root) {
        printf( "%2d: root gather:   [ %s ]\n",
                mpi_rank, to_string( recv_buf ).c_str() );
    }
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int error = 0;

    mpi_call( MPI_Init( &argc, &argv ) );

    try {
        test( false );
        test( true  );
    }
    catch (std::exception& ex) {
        printf( "%s\n", ex.what() );
        error = -1;
    }

    mpi_call( MPI_Finalize() );
    return error;
}
