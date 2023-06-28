// Demonstrates difference in speed for sqrt vs. pow.
// Doesn't explicitly time them, but for large n it is obvious.

#include <cmath>
#include <vector>
#include <cstdio>

int main( int argc, char** argv )
{
    int n = 10000000;
    if (argc > 1)
        n = atoi( argv[1] );
    printf( "n %d\n", n );
    std::vector<double> x( n );

    for (int j = 0; j < 10; ++j) {
        printf( "sqrt j %d\n", j );
        for (int i = 0; i < n; ++i) {
            x[i] = sqrt( i );
        }
    }

    for (int j = 0; j < 10; ++j) {
        printf( "pow  j %d\n", j );
        for (int i = 0; i < n; ++i) {
            x[i] = pow( i, 0.5 );
        }
    }

    return 0;
}
