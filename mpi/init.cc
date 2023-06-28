#include <stdio.h>
#include <mpi.h>

#include "util.hh"

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int mpi_rank, mpi_size;
    mpi_call( MPI_Init( &argc, &argv ) );
    mpi_call( MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank ) );
    mpi_call( MPI_Comm_size( MPI_COMM_WORLD, &mpi_size ) );

    printf( "rank %2d, size %2d\n", mpi_rank, mpi_size );

    mpi_call( MPI_Finalize() );
    return 0;
}
