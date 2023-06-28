// Demonstrates the syntax for different template operations.

#include <complex>
#include <stdio.h>

//------------------------------------------------------------------------------
// Template: foo<T>( T data )
template <typename T>
void foo( T data )
{
    printf( "foo<T>( T data = %7.4f, sizeof(T) %lu )\n",
            double(data), sizeof(T) );
}

//------------------------------------------------------------------------------
// Instantiate. (Not needed here, since main can see the definition above.)
template
void foo( float data );

//------------------------------------------------------------------------------
// Specialize: foo<T>( T data ) with T = double.
template <>
void foo( double data )
{
    printf( "foo<T>( T data = %7.4f, sizeof(T) %lu ) specialize for T = double\n",
            data, sizeof(double) );
}

//------------------------------------------------------------------------------
// Overload: foo<T>( complex<T> data )
template <typename T>
void foo( std::complex<T> data )
{
    printf( "foo<T>( complex<T> data = %7.4f + %7.4fi ), sizeof(T) %lu\n",
            double( real( data ) ),
            double( imag( data ) ),
            sizeof(T) );
}

//------------------------------------------------------------------------------
// Overload: foo<T>( T data1, T data2 )
template <typename T>
void foo( T data1, T data2 )
{
    printf( "foo<T>( T data1 = %7.4f, T data2 = %7.4f, sizeof(T) %lu )\n",
            double( data1 ),
            double( data2 ),
            sizeof(T) );
}

//------------------------------------------------------------------------------
int main()
{
    foo( 1 );
    foo( 1L );
    foo( 1.234 );   // double overload
    foo( 1.234f );
    foo( std::complex<float>( 1.234, 4.567 ) );     // complex overload
    foo( std::complex<double>( 1.234, 4.567 ) );    // complex overload
    foo( 1.234, 4.567 );    // data1, data2 overload
    return 0;
}
