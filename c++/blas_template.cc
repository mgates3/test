/*

Test calling optimized vs. templated BLAS. See
https://bitbucket.org/icl/blaspp/pull-requests/28#comment-206149980

# Uses optimized BLAS unless specifically calling template gemm<TA, TB, TC>()
# or mixed precision doesn't match optimized version.
>>> g++ -Wall -std=c++11 -o blas_optimized blas.cc
>>> ./blas_optimized
gemm( sA, sB, sC )                            => gemm( float, float, float ) optimized
gemm<float, float, float>( sA, sB, sC )       => gemm( TA=float, TB=float, TC=float )

gemm( dA, dB, dC )                            => gemm( double, double, double ) optimized
gemm<double, double, double>( dA, dB, dC )    => gemm( TA=double, TB=double, TC=double )

gemm( dA, sB, dC )                            => gemm( TA=double, TB=float, TC=double )
gemm<double, float, double>( dA, sB, dC )     => gemm( TA=double, TB=float, TC=double )


# Uses template all the time.
>>> g++ -Wall -std=c++11 -o blas_use_template blas.cc -DBLAS_USE_TEMPLATE
>>> ./blas_use_template
gemm( sA, sB, sC )                            => gemm( TA=float, TB=float, TC=float )
gemm<float, float, float>( sA, sB, sC )       => gemm( TA=float, TB=float, TC=float )

gemm( dA, dB, dC )                            => gemm( TA=double, TB=double, TC=double )
gemm<double, double, double>( dA, dB, dC )    => gemm( TA=double, TB=double, TC=double )

gemm( dA, sB, dC )                            => gemm( TA=double, TB=float, TC=double )
gemm<double, float, double>( dA, sB, dC )     => gemm( TA=double, TB=float, TC=double )


# Doesn't link due to undefined implementation of optimized BLAS.
>>> g++ -Wall -std=c++11 -o blas_no_impl blas.cc -DBLAS_NO_IMPL
Undefined symbols for architecture x86_64:
  "__Z4gemmPKdS0_Pd", referenced from:
      _main in cc7YxGpw.o
  "__Z4gemmPKfS0_Pf", referenced from:
      _main in cc7YxGpw.o
ld: symbol(s) not found for architecture x86_64
collect2: error: ld returned 1 exit status

*/


#include <stdio.h>

#include "get_type_name.hh"

//------------------------------------------------------------------------------
// optimized gemm prototypes (in headers)

#define BLAS_USE_TEMPLATE
#ifndef BLAS_USE_TEMPLATE
void gemm( int64_t m, int64_t n, int64_t k, float const* A, float const* B, float beta, float* C );
void gemm( int64_t m, int64_t n, int64_t k, double const* A, double const* B, double beta, double* C );
#endif  // BLAS_USE_TEMPLATE


//------------------------------------------------------------------------------
// template gemm implementation, 1 type (in headers)
namespace impl {

template <typename T>
void gemm( int64_t m, int64_t n, int64_t k, T const* A, T const* B, T beta, T* C )
{
    printf( "gemm( T=%s ) templated implementation (1 type)\n",
            get_type_name<T>().c_str() );
}

};

void gemm( int64_t m, int64_t n, int64_t k, T const* A, T const* B, T beta, T* C )
{
    impl::gemm( m, n, k, A, B, beta, C );
}

void gemm( int64_t m, int64_t n, int64_t k, T const* A, T const* B, T beta, T* C )
{
    impl::gemm( m, n, k, A, B, beta, C );
}


//------------------------------------------------------------------------------
// templated gemm implementation, 3 types (in headers)

template <typename TA, typename TB, typename TC>
void gemm( int64_t m, int64_t n, int64_t k, TA const* A, TB const* B, TC beta, TC* C )
{
    printf( "gemm( TA=%s, TB=%s, TC=%s ) templated implementation (3 types)\n",
            get_type_name<TA>().c_str(),
            get_type_name<TB>().c_str(),
            get_type_name<TC>().c_str() );
}


//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    const int n = 2;
    float  sbeta = 1.0;
    double dbeta = 1.0;
    int    ibeta = 1;
    float  sA[ n*n ], sB[ n*n ], sC[ n*n ];
    double dA[ n*n ], dB[ n*n ], dC[ n*n ];
    int    iA[ n*n ], iB[ n*n ], iC[ n*n ];
    const int64_t n64 = n;

    //----- single
    printf( "%-48s => ", "gemm( int,   sA, sB, sbeta, sC )" );
    gemm( n,   n,   n,   sA, sB, 1.0f, sC );
    printf( "%-48s => ", "gemm( int,   sA, sB, dbeta, sC )" );
    gemm( n,   n,   n,   sA, sB, 1.0, sC );  // error
    printf( "%-48s => ", "gemm( int64, sA, sB, sbeta, sC )" );
    gemm( n64, n64, n64, sA, sB, sbeta, sC );
    printf( "%-48s => ", "gemm( int64, sA, sB, dbeta, sC )" );
    gemm( n64, n64, n64, sA, sB, dbeta, sC );  // error

    printf( "%-48s => ", "gemm<float>( int,   sA, sB, sbeta, sC )" );
    gemm<float>( n,   n,   n,   sA, sB, sbeta, sC );
    printf( "%-48s => ", "gemm<float>( int64, sA, sB, sbeta, sC )" );
    gemm<float>( n64, n64, n64, sA, sB, sbeta, sC );

    printf( "%-48s => ", "gemm<float, float, float>( int,   sA, sB, sbeta, sC )" );
    gemm<float, float, float>( n,   n,   n,   sA, sB, sbeta, sC );
    printf( "%-48s => ", "gemm<float, float, float>( int64, sA, sB, sbeta, sC )" );
    gemm<float, float, float>( n64, n64, n64, sA, sB, sbeta, sC );
    printf( "\n" );

    //----- double
    printf( "%-48s => ", "gemm( dA, dB, dbeta, dC )" );
    gemm( n,   n,   n,   dA, dB, dbeta, dC );

    printf( "%-48s => ", "gemm<double>( dA, dB, dbeta, dC )" );
    gemm<double>( n,   n,   n,   dA, dB, dbeta, dC );

    printf( "%-48s => ", "gemm<double, double, double>( dA, dB, dbeta, dC )" );
    gemm<double, double, double>( n,   n,   n,   dA, dB, dbeta, dC );
    printf( "\n" );

    //----- mixed
    printf( "%-48s => ", "gemm( dA, sB, dbeta, dC )" );
    gemm( n,   n,   n,   dA, sB, dbeta, dC );

    printf( "%-48s => ", "gemm<double, float, double>( dA, sB, dbeta, dC )" );
    gemm<double, float, double>( n,   n,   n,   dA, sB, dbeta, dC );
    printf( "\n" );

    //----- integer
    printf( "%-48s => ", "gemm( int,   iA, iB, iC )" );
    gemm( n,   n,   n,   iA, iB, ibeta, iC );
    printf( "%-48s => ", "gemm( int64, iA, iB, iC )" );
    gemm( n64, n64, n64, iA, iB, ibeta, iC );

    printf( "%-48s => ", "gemm<int>( int,   iA, iB, iC )" );
    gemm<int>( n,   n,   n,   iA, iB, ibeta, iC );
    printf( "%-48s => ", "gemm<int>( int64, iA, iB, iC )" );
    gemm<int>( n64, n64, n64, iA, iB, ibeta, iC );

    printf( "%-48s => ", "gemm<int, int, int>( int,   iA, iB, iC )" );
    gemm<int, int, int>( n,   n,   n,   iA, iB, ibeta, iC );
    printf( "%-48s => ", "gemm<int, int, int>( int64, iA, iB, iC )" );
    gemm<int, int, int>( n64, n64, n64, iA, iB, ibeta, iC );
    printf( "\n" );

    return 0;
}


//------------------------------------------------------------------------------
// optimized gemm implementation (e.g., src/gemm.cc)

#ifndef BLAS_NO_IMPL
void gemm( int64_t m, int64_t n, int64_t k, float const* A, float const* B, float beta, float* C )
{
    printf( "gemm( int64_t, float*, float*, float, float* ) optimized\n" );
}

void gemm( int64_t m, int64_t n, int64_t k, double const* A, double const* B, double beta, double* C )
{
    printf( "gemm( int64_t, double*, double*, double, double* ) optimized\n" );
}
#endif  // BLAS_NO_IMPL
