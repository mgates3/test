#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

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
        double t_total = MPI_Wtime();
        for (int i = 0; i < n; ++i) {
            t = MPI_Wtime();
            x[ i ] += i;
            x[ i ] = MPI_Wtime() - t;
        }
        t_total = MPI_Wtime() - t_total;

        double t_total2 = MPI_Wtime();
        for (int i = 0; i < n; ++i) {
            if (verbose) t = MPI_Wtime();
            x[ i ] += i;
            if (verbose) x[ i ] = MPI_Wtime() - t;
        }
        t_total2 = MPI_Wtime() - t_total2;

        double t_total3 = MPI_Wtime();
        for (int i = 0; i < n; ++i) {
            x[ i ] += i;
        }
        t_total3 = MPI_Wtime() - t_total3;

        printf( "n %d, time %.6f, time2 %.6f, time3 %.6f\n", n, t_total, t_total2, t_total3 );
    }

    delete[] x;
    return 0;
}
