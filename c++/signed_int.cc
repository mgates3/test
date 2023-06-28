#include <stdio.h>

int main( int argc, char** argv )
{
    typedef long long llong;
    typedef unsigned long long ullong;

    int n = 10;

    printf( "int64_t\n" );
    for (int64_t i = n-1; i >= 0; --i) {
        printf( "i %lld\n", llong( i ) );
    }

    printf( "size_t\n" );
    for (size_t i = n-1; i >= 0; --i) {
        printf( "i %llu\n", ullong( i ) );
    }

    return 0;
}
