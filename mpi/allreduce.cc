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
    std::vector<double> send_buf( n );
    std::iota( send_buf.begin(), send_buf.end(), 10*mpi_rank );

    // Everyone needs recv_buf (unlike MPI_Gather) unless in_place.
    std::vector<double> recv_buf( n, -1 );

    // Everyone sends.
    printf( "%2d: send:   [ %s ]\n",
            mpi_rank, to_string( send_buf ).c_str() );

    // Pre-defined reductions:
    // MPI_MAX     maximum
    // MPI_MIN     minimum
    // MPI_SUM     sum
    // MPI_PROD    product
    // MPI_LAND    logical and
    // MPI_BAND    bit-wise and
    // MPI_LOR     logical or
    // MPI_BOR     bit-wise or
    // MPI_LXOR    logical xor
    // MPI_BXOR    bit-wise xor
    // MPI_MAXLOC  max value and location
    // MPI_MINLOC  min value and location
    if (in_place) {
        //--------------------
        mpi_call(
            MPI_Allreduce( MPI_IN_PLACE, &send_buf[0], n, MPI_DOUBLE, MPI_SUM,
                           comm ) );

        // Everyone receives.
        printf( "%2d: reduce: [ %s ] (in-place)\n",
                mpi_rank, to_string( send_buf ).c_str() );
    }
    else {
        //--------------------
        mpi_call(
            MPI_Allreduce( &send_buf[0], &recv_buf[0], n, MPI_DOUBLE, MPI_SUM,
                           comm ) );

        // Everyone receives.
        printf( "%2d: reduce: [ %s ]\n",
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
