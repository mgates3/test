#include <mpi.h>
#include <stdio.h>

int main( int argc, char** argv )
{
    MPI_Init( &argc, &argv );

    int mpi_rank, mpi_size;
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank );
    MPI_Comm_size( MPI_COMM_WORLD, &mpi_size );

    char mpi_name[ MPI_MAX_PROCESSOR_NAME ];
    int len;
    MPI_Get_processor_name( mpi_name, &len );

    printf( "rank %3d, size %3d, name %s\n", mpi_rank, mpi_size, mpi_name );

    MPI_Finalize();
}
