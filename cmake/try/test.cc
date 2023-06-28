#include <stdio.h>

void foo();

extern "C"
void dgemm_( const char*, const char*, int*, int*, int*,
             double*, double*, int*,
             double*, int*,
             double*, double*, int* );

int main( int argc, char** argv )
{
    #ifdef FOO
    printf( "FOO %d\n", FOO );
    #endif

    #ifdef BAZ
    printf( "BAZ %d\n", BAZ );
    #endif

    printf( "__cplusplus %ld\n", __cplusplus );

    printf( "dgemm\n" );
    int n = 10;
    double alpha = 1;
    double beta  = 1;
    double A[ 10*10 ], B[ 10*10 ], C[ 10*10 ];
    dgemm_( "no", "no", &n, &n, &n, &alpha, A, &n, B, &n, &beta, C, &n );

    foo();

    fprintf( stderr, "stderr test\n" );

    return 0;
}
