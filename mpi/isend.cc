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
    std::vector<double> send_buf( n );
    std::vector<double> recv_buf( n, -1 );
    std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );
    MPI_Request requests[2];
    // MPI_Status  statuses[2];

    // Send to next higher rank, in cycle. Send from send_buf; recv into recv_buf.
    // Isend avoids deadlock when everyone blocks in send for recv that
    // never happens. Irecv could be Recv, then use MPI_Wait on send request.
    int dst = (mpi_rank + 1) % mpi_size;
    int src = mpi_rank - 1;
    if (src < 0)
        src = mpi_size - 1;

    //--------------------
    mpi_call(
        MPI_Isend( &send_buf[0], n, MPI_DOUBLE, dst, tag_0, comm, &requests[0] ) );
    mpi_call(
        MPI_Irecv( &recv_buf[0], n, MPI_DOUBLE, src, tag_0, comm, &requests[1] ) );
    mpi_call(
        MPI_Waitall( 2, requests, MPI_STATUSES_IGNORE ) );
    // alt: MPI_Waitall( 2, requests, statuses )
    // alt: MPI_Wait( &requests[0], MPI_STATUS_IGNORE ) );
    //      MPI_Wait( &requests[1], MPI_STATUS_IGNORE ) );
    printf( "%2d: send to   %2d: [ %s ]\n"
            "%2d: recv from %2d: [ %s ]\n",
            mpi_rank, dst, to_string( send_buf ).c_str(),
            mpi_rank, src, to_string( recv_buf ).c_str() );
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
