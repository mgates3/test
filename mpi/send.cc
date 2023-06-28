#include <stdio.h>
#include <mpi.h>
#include <vector>
#include <numeric>

#include "util.hh"

//------------------------------------------------------------------------------
void test()
{
    // Constants
    const int tag_0 = 0;

    int mpi_rank, mpi_size;
    MPI_Comm comm = MPI_COMM_WORLD;
    mpi_call( MPI_Comm_rank( comm, &mpi_rank ) );
    mpi_call( MPI_Comm_size( comm, &mpi_size ) );
    printf( "rank %2d, size %2d\n", mpi_rank, mpi_size );
    MPI_Barrier( comm );  // help order prints (still not guaranteed).

    int n = 4;
    std::vector<double> buf( n );
    std::iota( buf.begin(), buf.end(), 10*mpi_rank );

    // Even ranks send to odd ranks
    if (mpi_rank % 2 == 0) {
        int dst = mpi_rank + 1;
        if (dst < mpi_size) {
            mpi_call(
                MPI_Send( &buf[0], n, MPI_DOUBLE, dst, tag_0, comm ) );
            printf( "%2d: send to   %2d: [ %s ]\n",
                    mpi_rank, dst, to_string( buf ).c_str() );
        }
    }
    else {
        int src = mpi_rank - 1;
        // MPI_Status status;
        mpi_call(
            MPI_Recv( &buf[0], n, MPI_DOUBLE, src, tag_0, comm,
                      MPI_STATUS_IGNORE ) );
        // alt: MPI_Recv( &buf[0], n, MPI_DOUBLE, src, tag_0, comm, &status )
        printf( "%2d: recv from %2d: [ %s ]\n",
                mpi_rank, src, to_string( buf ).c_str() );
    }
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int error = 0;

    mpi_call( MPI_Init( &argc, &argv ) );

    try {
        test();
    }
    catch (std::exception& ex) {
        printf( "%s\n", ex.what() );
        error = -1;
    }

    mpi_call( MPI_Finalize() );
    return error;
}
