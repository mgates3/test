#include <blas.hh>

#include <stdio.h>

int main( int argc, char** argv )
{
    printf( "%s\n", __func__ );
    blas::gemm();
    blas::hemm();
    blas::herk();
    blas::her2k();
    blas::trmm();
    blas::trsm();
    return 0;
}
