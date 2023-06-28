#include <stdio.h>

#include "instantiate.hh"

template <typename matrix_type>
void norm( matrix_type& A )
{
    printf( "%s\n", __PRETTY_FUNCTION__ );
}

// Instantiations.
template
void norm( Matrix<float>& x );

template
void norm( Matrix<double>& x );

template
void norm( TrapezoidMatrix<float>& x );

template
void norm( TrapezoidMatrix<double>& x );

template <typename T>
void norm( TriangularMatrix<T>& x )
{
    printf( "TriangularMatrix wrapper\n" );
    norm< TrapezoidMatrix<T> >( x );
}

template
void norm( TriangularMatrix<float>& x );

template
void norm( TriangularMatrix<double>& x );
