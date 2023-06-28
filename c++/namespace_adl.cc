// Demonstrates use of Argument-Dependent Lookup (ADL) to find functions.

#include <stdio.h>

namespace blas {

enum class Layout { ColMajor, RowMajor };

void geru( Layout layout, int m, int n )
{
    printf( "%s( layout %d, m %d, n %d )\n", __func__, int(layout), m, n );
}

void geru2( int m, int n )
{
    printf( "%s( m %d, n %d )\n", __func__, m, n );
}

} // namespace blas

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int m = 100;
    int n = 200;

    // Finds geru based on ADL of blas::Layout.
    geru( blas::Layout::ColMajor, m, n );

    #ifdef ERROR
        // error: 'geru2' was not declared in this scope; did you mean 'blas::geru2'?
        geru2( m, n );
    #endif

    return 0;
}
