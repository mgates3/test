// Compares abs, which does `int abs( int )`,
// with std::abs, which does `double abs( double )`
// Output:
// x -1.2340, a  1.0000, b  1.2340

#include <cstdlib>
#include <cstdio>

int main( int argc, char** argv )
{
    double x = -1.234;
    double a = abs( x );
    double b = std::abs( x );
    printf( "x %7.4f, a %7.4f, b %7.4f\n", x, a, b );
    return 0;
}
