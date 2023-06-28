#include <stdio.h>

void foo( int a, int b=1, int c=2, int d=3 )
{
    printf( "a %d, b %d, c %d, d %d\n", a, b, c, d );
}

int main()
{
    foo( 1 );
    foo( 1, 5, 6, 7 );

    #if ERRORS
    foo( 1, b=9 );  // error: 'b' was not declared in this scope
    foo( 1, c=9 );  // error: 'c' was not declared in this scope
    #endif

    return 0;
}
