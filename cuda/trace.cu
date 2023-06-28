#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

// cuda
#include <nvToolsExt.h>

//------------------------------------------------------------------------------
namespace internal {
void task()
{
    nvtxRangePush( __func__ );
    int r = rand() % 1000;
    usleep( r );
    nvtxRangePop();
}
}

//------------------------------------------------------------------------------
void task()
{
    nvtxRangePush( __func__ );
    int r = rand() % 1000;
    usleep( r );
    nvtxRangePop();
}

//------------------------------------------------------------------------------
int main()
{
    printf( "hello\n" );
    task();
    
    int size = 1024;
    double *src, *dst;
    cudaError_t err;
    err = cudaMalloc( &src, size );
    assert( err == cudaSuccess );
    err = cudaMalloc( &dst, size );
    assert( err == cudaSuccess );
    err = cudaMemcpy( dst, src, size, cudaMemcpyDefault );
    assert( err == cudaSuccess );
    err = cudaFree( src );
    assert( err == cudaSuccess );
    err = cudaFree( dst );
    assert( err == cudaSuccess );
    
    internal::task();
    return 0;
}
