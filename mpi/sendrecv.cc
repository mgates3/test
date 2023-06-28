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

    int maxn = 4;
    int n = mpi_rank % maxn + 1;
    std::vector<double> send_buf( n );
    std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );

    // Send to next higher rank, in cycle.
    // Send from send_buf; receive into recv_buf.
    // Isend avoids deadlock when everyone blocks in send for recv that never happens.
    int dst = (mpi_rank + 1) % mpi_size;
    int src = mpi_rank - 1;
    if (src < 0)
        src = mpi_size - 1;

    int n_recv = src % maxn + 1;
    std::vector<double> recv_buf( n_recv, -1 );

    // MPI_Status  status;
    mpi_call(
        MPI_Sendrecv( &send_buf[0], n,      MPI_DOUBLE, dst, tag_0,
                      &recv_buf[0], n_recv, MPI_DOUBLE, src, tag_0,
                      comm, MPI_STATUS_IGNORE ) );
    // alt: MPI_Sendrecv( ..., &status )
    printf( "%2d: send %2d elements to   %2d: [ %s ]\n"
            "%2d: recv %2d elements from %2d: [ %s ]\n",
            mpi_rank, n,      dst, to_string( send_buf ).c_str(),
            mpi_rank, n_recv, src, to_string( recv_buf ).c_str() );
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
