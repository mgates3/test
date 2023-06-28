extern "C"
void dgemm_( const char* transA, const char* transB, int* m, int* n, int* k,
             double* alpha,
             double* A, int* lda,
             double* B, int* ldb,
             double* beta,
             double* C, int* ldc,
             unsigned transA_len, unsigned transB_len );

int main( int argc, char** argv )
{
    int n = 4;
    double A[ 4*4 ], B[ 4*4 ], C[ 4*4 ];
    double one = 1.0;
    dgemm_( "n", "n", &n, &n, &n, &one, A, &n, B, &n, &one, C, &n, 1, 1 );
    return 0;
}
