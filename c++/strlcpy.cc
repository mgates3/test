// Times strlcpy, strncpy, snprintf.
// strncpy copies up to n bytes, and zeros remaining bytes; medium speed (0.03 sec);
// doesn't guarantee null termination.
// strlcpy  copies up to n bytes, and guarantees null termination; fast (0.02 sec).
// snprintf copies up to n bytes, and guarantees null termination; slow (0.06 sec).
//
// thyme test/c++> ./strlcpy 
// initial  0.009434
// 
// strcpy   0.003168
// strcpy   0.001871
// strcpy   0.001821
// strcpy   0.001805
// strcpy   0.001796
// 
// strncpy  0.002925
// strncpy  0.002943
// strncpy  0.002915
// strncpy  0.002970
// strncpy  0.002906
// 
// strlcpy  0.001928
// strlcpy  0.001889
// strlcpy  0.001832
// strlcpy  0.001793
// strlcpy  0.001704
// 
// snprintf 0.007037
// snprintf 0.006754
// snprintf 0.006734
// snprintf 0.006510
// snprintf 0.006027

#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
double timer()
{
    struct timeval tv;
    gettimeofday( &tv, nullptr );
    return tv.tv_sec + tv.tv_usec*1e-6;
}

//------------------------------------------------------------------------------
int main()
{
    const int cnt = 100000;
    char dst[cnt][32];
    char src[cnt][32];
    
    //----------------------------------------
    // initialize
    double t = timer();
    for (int i = 0; i < cnt; ++i) {
        int len = rand() % 20;
        for (int j = 0; j < len; ++j) {
            src[i][j] = rand() % 26 + 'a';
        }
        src[i][len] = '\0';
    }
    t = timer() - t;
    printf( "initial  %.6f\n\n", t );
    
    //----------------------------------------
    for (int k = 0; k < 5; ++k) {
        t = timer();
        for (int i = 0; i < cnt; ++i) {
            strcpy( dst[i], src[i] );
        }
        t = timer() - t;
        printf( "strcpy   %.6f\n", t );
    }
    printf( "\n" );
    
    //----------------------------------------
    for (int k = 0; k < 5; ++k) {
        t = timer();
        for (int i = 0; i < cnt; ++i) {
            strncpy( dst[i], src[i], 32 );
        }
        t = timer() - t;
        printf( "strncpy  %.6f\n", t );
    }
    printf( "\n" );
    
    //----------------------------------------
    for (int k = 0; k < 5; ++k) {
        t = timer();
        for (int i = 0; i < cnt; ++i) {
            strlcpy( dst[i], src[i], 32 );
        }
        t = timer() - t;
        printf( "strlcpy  %.6f\n", t );
    }
    printf( "\n" );
    
    //----------------------------------------
    for (int k = 0; k < 5; ++k) {
        t = timer();
        for (int i = 0; i < cnt; ++i) {
            snprintf( dst[i], 32, "%s", src[i] );
        }
        t = timer() - t;
        printf( "snprintf %.6f\n", t );
    }
    printf( "\n" );
    return 0;
}
