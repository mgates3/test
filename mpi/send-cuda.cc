// Tests whether MPI is GPU-aware.
// With Open MPI on Leconte:
//
// sh leconte mpi> make send-cuda
// mpicxx -Wall -std=c++14 -c -o send-cuda.o send-cuda.cc
// mpicxx  -o send-cuda send-cuda.o \
// 	-lcudart
//
// # stable sort orders rank 0 output, then rank 1.
// # I deleted some MPI error messages related to "OpenFabrics device".
// leconte> mpirun -np 2 ./send-cuda | sort -n -s
// rank  0, size  2
// rank  1, size  2
//  0: initial     : [    0.0   1.0   2.0   3.0 ] host to host
//  0: send to    1: [    0.0   1.0   2.0   3.0 ] host to host
//  0: initial     : [    0.0   1.0   2.0   3.0 ] host to dev
//  0: send to    1: [    0.0   1.0   2.0   3.0 ] host to dev
//  0: initial     : [    0.0   1.0   2.0   3.0 ] dev  to host
//  0: send to    1: [    0.0   1.0   2.0   3.0 ] dev  to host
//  0: initial     : [    0.0   1.0   2.0   3.0 ] dev  to dev
//  0: send to    1: [    0.0   1.0   2.0   3.0 ] dev  to dev
//  1: initial     : [   10.0  11.0  12.0  13.0 ] host to host
//  1: recv from  0: [    0.0   1.0   2.0   3.0 ] host to host
//  1: initial     : [   10.0  11.0  12.0  13.0 ] host to dev
//  1: recv from  0: [    0.0   1.0   2.0   3.0 ] host to dev
//  1: initial     : [   10.0  11.0  12.0  13.0 ] dev  to host
//  1: recv from  0: [    0.0   1.0   2.0   3.0 ] dev  to host
//  1: initial     : [   10.0  11.0  12.0  13.0 ] dev  to dev
//  1: recv from  0: [    0.0   1.0   2.0   3.0 ] dev  to dev

#include <stdio.h>
#include <mpi.h>
#include <vector>
#include <numeric>

#include <cuda_runtime.h>

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

    cudaSetDevice( 0 );
    double* dbuf;
    cudaMalloc( &dbuf, n * sizeof(double) );

    const char* name;
    double *src, *dst;

    for (int mode = 0; mode < 4; ++mode) {
        // Select src and dst on CPU host or GPU device.
        switch (mode) {
            case 0: src =  &buf[0], dst =  &buf[0]; name = "host to host"; break;
            case 1: src =  &buf[0], dst = &dbuf[0]; name = "host to dev";  break;
            case 2: src = &dbuf[0], dst =  &buf[0]; name = "dev  to host"; break;
            case 3: src = &dbuf[0], dst = &dbuf[0]; name = "dev  to dev";  break;
        }

        // Initialize data.
        std::iota( buf.begin(), buf.end(), 10*mpi_rank );
        cudaMemcpy( dbuf, &buf[0], n * sizeof(double), cudaMemcpyDefault );
        printf( "%2d: initial     : [ %s ] %s\n",
                mpi_rank, to_string( buf ).c_str(), name );

        // Even ranks send to odd ranks
        if (mpi_rank % 2 == 0) {
            int dst = mpi_rank + 1;
            if (dst < mpi_size) {
                // memcpy: dst, src
                mpi_call(
                    MPI_Send( src, n, MPI_DOUBLE, dst, tag_0, comm ) );
                printf( "%2d: send to   %2d: [ %s ] %s\n",
                        mpi_rank, dst, to_string( buf ).c_str(), name );
            }
        }
        else {
            int src = mpi_rank - 1;
            // MPI_Status status;
            mpi_call(
                MPI_Recv( dst, n, MPI_DOUBLE, src, tag_0, comm,
                          MPI_STATUS_IGNORE ) );
            // alt with status:
            //  MPI_Recv( dst, n, MPI_DOUBLE, src, tag_0, comm, &status )
            if (mode == 1 || mode == 3)
                cudaMemcpy( &buf[0], dbuf, n * sizeof(double), cudaMemcpyDefault );
            printf( "%2d: recv from %2d: [ %s ] %s\n",
                    mpi_rank, src, to_string( buf ).c_str(), name );
        }
    }

    cudaFree( dbuf );
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
