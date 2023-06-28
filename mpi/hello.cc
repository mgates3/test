#include <stdio.h>
#include <mpi.h>

#include "util.hh"

int main( int argc, char** argv )
{
    const int tag_0 = 0;
    int mpi_rank, mpi_size;
    int buf[ 1024 ];
    int cnt = sizeof( buf ) / sizeof( *buf );

    mpi_call( MPI_Init( &argc, &argv ) );
    mpi_call( MPI_Comm_size( MPI_COMM_WORLD, &mpi_size ) );
    mpi_call( MPI_Comm_rank( MPI_COMM_WORLD, &mpi_rank ) );

    if (mpi_rank != 0) {
        mpi_call( MPI_Recv( buf, cnt, MPI_INT, 0, tag_0, MPI_COMM_WORLD, MPI_STATUS_IGNORE ) );
        printf( "%2d: recv [ %2d, ... ]\n", mpi_rank, buf[ 0 ] );
    }
    else {
        for (int dst = 1; dst < mpi_size; ++dst) {
            buf[ 0 ] = 1000 + dst;
            mpi_call( MPI_Send( buf, cnt, MPI_INT, dst, tag_0, MPI_COMM_WORLD ) );
        }
    }

    if (mpi_rank == 0) {
        printf( "%2d: done\n", mpi_rank );
    }

    mpi_call( MPI_Finalize() );
    return 0;
}
