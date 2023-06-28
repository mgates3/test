#include <omp.h>
#include <stdio.h>

int main( int argc, char** argv )
{
    double x[ 1000 ] = { 0 };
    
    #pragma omp parallel for
    for (int i = 0; i < 1000; ++i) {
        x[i] += i;
    }
    
    // max_threads can be used outside parallel;
    // num_threads must be inside parallel.
    int max_threads = omp_get_max_threads();
    printf( "max_threads %d\n", max_threads );
    
    return 0;
}
