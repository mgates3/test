// tests calling malloc routine, which has size_t argument,
// with int and int64, per
// https://bitbucket.org/icl/magma/issues/35/magma_sgesv_gpu-returned-error-112-cannot

#include <stddef.h>
#include <stdio.h>

void magma_malloc( void* ptr, size_t size )
{
    printf( "%s( ptr, size=%lu )\n", __func__, size );
}

int main( int argc, char** argv )
{
    int     n32 = 47000;
    int64_t n64 = 47000;
    double* x;

    magma_malloc( &x, n32*n32 );            // fails, n*n overflows
    magma_malloc( &x, size_t(n32)*n32 );    // ok, C++ syntax
    magma_malloc( &x, (size_t)n32*n32 );    // ok, C syntax

    magma_malloc( &x, n64*n64 );            // ok
    magma_malloc( &x, size_t(n64)*n64 );    // ok
    magma_malloc( &x, (size_t)n64*n64 );    // ok

    return 0;
}
