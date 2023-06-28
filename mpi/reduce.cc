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

    int root = mpi_size - 1;  // last process

    // recv_buf needed only on root process.
    std::vector<double> recv_buf( 1, -1 );
    if (mpi_rank == root && ! in_place) {
        recv_buf.resize( n, -1 );
    }

    // Everyone including root sends.
    printf( "%2d: send to %2d:  [ %s ]\n",
            mpi_rank, root, to_string( send_buf ).c_str() );

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

    // Note MPI_IN_PLACE is only on root process, otherwise it errors.
    if (mpi_rank == root && in_place) {
        //--------------------
        mpi_call(
            MPI_Reduce( MPI_IN_PLACE, &send_buf[0], n, MPI_DOUBLE, MPI_SUM,
                        root, comm ) );
    }
    else {
        //--------------------
        mpi_call(
            MPI_Reduce( &send_buf[0], &recv_buf[0], n, MPI_DOUBLE, MPI_SUM,
                        root, comm ) );
    }

    // Only root receives.
    if (mpi_rank == root) {
        if (in_place) {
            printf( "%2d: root reduce: [ %s ] (in-place)\n",
                    mpi_rank, to_string( send_buf ).c_str() );
        }
        else {
            printf( "%2d: root reduce: [ %s ]\n",
                    mpi_rank, to_string( recv_buf ).c_str() );
        }
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
