#include <stdio.h>
#include <mpi.h>
#include <vector>
#include <numeric>

#include "util.hh"

//------------------------------------------------------------------------------
void test()
{
    int mpi_rank, mpi_size;
    MPI_Comm comm = MPI_COMM_WORLD;
    mpi_call( MPI_Comm_rank( comm, &mpi_rank ) );
    mpi_call( MPI_Comm_size( comm, &mpi_size ) );
    printf( "rank %2d, size %2d\n", mpi_rank, mpi_size );
    MPI_Barrier( comm );  // help order prints (still not guaranteed).

    int n = 4;
    std::vector<double> buf( n );
    std::iota( buf.begin(), buf.end(), 10*mpi_rank );

    int root = mpi_size - 1;  // last process

    //--------------------
printf( "bcast\n" );
    mpi_call(
        MPI_Bcast( &buf[0], n, MPI_DOUBLE, root, comm ) );
printf( "bcast done\n" );

    if (mpi_rank == root) {
        printf( "%2d: bcast root send:    [ %s ]\n",
                mpi_rank, to_string( buf ).c_str() );
    }
    else {
        printf( "%2d: bcast recv from %2d: [ %s ]\n",
                mpi_rank, root, to_string( buf ).c_str() );
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
