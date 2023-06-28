#include <mpi.h>

int main( int argc, char** argv )
{
    MPI_Init( &argc, &argv );

    int mpi_rank;
    MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank );

    MPI_Comm local_comm;
    MPI_Comm_split_type( MPI_COMM_WORLD, MPI_COMM_TYPE_SHARED, 0,
                         MPI_INFO_NULL, &local_comm );
    int local_rank;
    MPI_Comm_rank( local_comm, &local_rank );

    printf( "mpi rank %d, local rank %d\n", mpi_rank, local_rank );

    MPI_Finalize();
}
