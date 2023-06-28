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
    std::vector<double> recv_buf( n, -1 );

    int root = 0;

    // send_buf, send_cnts, send_offsets needed only on root process.
    int size = 1;
    std::vector<double> send_buf( size, -1 );
    std::vector<int> send_cnts( 1, -1 ), send_offsets( 1, -1 );
    if (mpi_rank == root) {
        send_cnts.resize( mpi_size );
        for (int r = 0; r < mpi_size; ++r) {
            send_cnts[ r ] = r % maxn + 1;
        }

        // Do one extra entry to get size.
        send_offsets.resize( mpi_size + 1 );
        send_offsets[ 0 ] = 0;
        std::partial_sum( &send_cnts[ 0 ], &send_cnts[ mpi_size ],
                          &send_offsets[ 1 ] );
        printf( "%2d: send_cnts           [ %s ]\n",
                mpi_rank, to_string( send_cnts    ).c_str() );
        printf( "%2d: send_offsets        [ %s ]\n",
                mpi_rank, to_string( send_offsets ).c_str() );

        size = send_offsets[ mpi_size ];
        send_buf.resize( size, -1 );
        std::iota( send_buf.begin(), send_buf.end(), mpi_rank );

        // Only root sends.
        printf( "%2d: bcast root scatter: [ %s ]\n",
                mpi_rank, to_string( send_buf ).c_str() );
    }

    if (mpi_rank == root && in_place) {
        //--------------------
        mpi_call(
           MPI_Scatterv( &send_buf[0], &send_cnts[0], &send_offsets[0], MPI_DOUBLE,
                         MPI_IN_PLACE, n, MPI_DOUBLE, root, comm ) );
    }
    else {
        //--------------------
        mpi_call(
           MPI_Scatterv( &send_buf[0], &send_cnts[0], &send_offsets[0], MPI_DOUBLE,
                         &recv_buf[0], n, MPI_DOUBLE, root, comm ) );

        // Everyone including root (unless in_place) receives.
        printf( "%2d: bcast recv from %2d: [ %s ]\n",
                mpi_rank, root, to_string( recv_buf ).c_str() );
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
