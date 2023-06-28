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

    int n = 4;
    int root = mpi_size - 1;  // last process

    // recv_buf needed only on root process.
    int size = 1;
    std::vector<double> recv_buf( size, -1 );
    if (mpi_rank == root) {
        size = n * mpi_size;
        recv_buf.resize( size, -1 );
    }

    if (mpi_rank == root && in_place) {
        // Everyone including root sends.
        // Initialize in-place.
        std::iota( &recv_buf[ n * mpi_rank ],
                   &recv_buf[ n * (mpi_rank + 1) ],
                   10*mpi_rank );
        printf( "%2d: send to %2d:  [ %s ] (in-place)\n",
                mpi_rank, root, to_string( recv_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Gather( MPI_IN_PLACE, n, MPI_DOUBLE,
                        &recv_buf[0], n, MPI_DOUBLE, root, comm ) );
    }
    else {
        // Everyone including root sends.
        std::vector<double> send_buf( n );
        std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );
        printf( "%2d: send to %2d:  [ %s ]\n",
                mpi_rank, root, to_string( send_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Gather( &send_buf[0], n, MPI_DOUBLE,
                        &recv_buf[0], n, MPI_DOUBLE, root, comm ) );
    }

    // Only root receives.
    if (mpi_rank == root) {
        printf( "%2d: root gather: [ %s ]\n",
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
