// https://gist.github.com/mgates3/46ee36e11d6488ff5d81adcc29f88ee8

// Demonstrates const correctness with double pointer (**).
// See https://isocpp.org/wiki/faq/const-correctness#constptrptr-conversion

//------------------------------------------------------------------------------
void nested1( int** xx )
{
    int*       x1 = xx[ 0 ];
    int const* x2 = xx[ 0 ];
}

// Correctly prohibits conversion to non-const `int* x`,
// but can't be called with `int** x` (see main).
void nested2( int const** xx )
{
  //int*       x1 = xx[ 0 ];  // error: invalid conversion from 'const int*' to 'int*'
    int const* x2 = xx[ 0 ];
}

// Doesn't prohibit conversion to non-const `int* x`,
// so isn't doing what we might want.
void nested3( int* const* xx )
{
    int*       x1 = xx[ 0 ];
    int const* x2 = xx[ 0 ];
}

// Correctly prohibits conversion to non-const `int* x`,
// and can be called with `int** x` (see main).
void nested4( int const* const* xx )
{
  //int*       x1 = xx[ 0 ];  // error: invalid conversion from 'const int*' to 'int*'
    int const* x2 = xx[ 0 ];
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int x[ 4 ];
    int* xx[ 4 ];

    nested1( xx );
  //nested2( xx );  // error: invalid conversion from 'int**' to 'const int**'
    nested3( xx );
    nested4( xx );

    int const* y = x;
    int const* const* yy = xx;

  //nested1( yy );  // error: invalid conversion from 'const int* const*' to 'int**'
  //nested2( yy );  // error: invalid conversion from 'const int* const*' to 'const int**'
  //nested3( yy );  // error: invalid conversion from 'const int* const*' to 'int* const*'
    nested4( yy );

    return 0;
}
