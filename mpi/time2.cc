#include <stdlib.h>
#include <stdio.h>

#include <sys/time.h>

double timer()
{
    struct timeval tv;
    gettimeofday( &tv, nullptr );
    return tv.tv_sec + tv.tv_usec*1e-6;
}

int main( int argc, char** argv )
{
    int n = 1000;
    int verbose = 0;
    if (argc > 1)
        n = atoi( argv[1] );
    if (argc > 2)
        verbose = atoi( argv[2] );
    printf( "n %d, verbose %d\n", n, verbose );

    double* x = new double[ n ];
    double t;

    for (int j = 0; j < 10; ++j) {
        double t_total = timer();
        for (int i = 0; i < n; ++i) {
            t = timer();
            x[ i ] += i;
            x[ i ] = timer() - t;
        }
        t_total = timer() - t_total;

        double t_total2 = timer();
        for (int i = 0; i < n; ++i) {
            if (verbose) t = timer();
            x[ i ] += i;
            if (verbose) x[ i ] = timer() - t;
        }
        t_total2 = timer() - t_total2;

        double t_total3 = timer();
        for (int i = 0; i < n; ++i) {
            x[ i ] += i;
        }
        t_total3 = timer() - t_total3;

        printf( "n %d, time %.6f, time2 %.6f, time3 %.6f\n", n, t_total, t_total2, t_total3 );
    }

    delete[] x;
    return 0;
}
