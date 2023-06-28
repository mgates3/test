#include <stdio.h>

int main( int argc, char** argv )
{
    printf( "%s\n", __func__ );

    #ifdef MAGMA_ILP64
    printf( "MAGMA_ILP64 %d\n", MAGMA_ILP64 );
    #endif

    #ifdef MKL_ILP64
    printf( "MKL_ILP64 %d\n", MKL_ILP64 );
    #endif

    return 0;
}
