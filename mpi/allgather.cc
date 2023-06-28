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

    // Everyone needs recv_buf (unlike MPI_Gather).
    int size = n * mpi_size;
    std::vector<double> recv_buf( size, -1 );

    if (in_place) {
        // Everyone including root sends.
        // Initialize in-place.
        std::iota( &recv_buf[ n*mpi_rank ],
                   &recv_buf[ n*(mpi_rank + 1) ],
                   10*mpi_rank );
        printf( "%2d: send:   [ %s ] (in-place)\n",
                mpi_rank, to_string( recv_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Allgather( MPI_IN_PLACE, n, MPI_DOUBLE,
                           &recv_buf[0], n, MPI_DOUBLE, comm ) );
    }
    else {
        // Everyone including root sends.
        std::vector<double> send_buf( n );
        std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );
        printf( "%2d: send:   [ %s ]\n",
                mpi_rank, to_string( send_buf ).c_str() );

        //--------------------
        mpi_call(
            MPI_Allgather( &send_buf[0], n, MPI_DOUBLE,
                           &recv_buf[0], n, MPI_DOUBLE, comm ) );
    }

    // Everyone receives (unlike MPI_Gather).
    printf( "%2d: gather: [ %s ]\n",
            mpi_rank, to_string( recv_buf ).c_str() );
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
