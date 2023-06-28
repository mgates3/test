#include <stdio.h>

#include <map>

enum class Option
{
    Lookahead,
    InnerBlocking,
    Time1,
    Time2,
    Time3,
    Time4,
};

typedef double Value;

//------------------------------------------------------------------------------
void foo( std::map< Option, Value > /* const */& opts )
{
    if (opts.count( Option::Time1 ) > 0)
        opts[ Option::Time1 ] = 1.111;
    if (opts.count( Option::Time2 ) > 0)
        opts[ Option::Time2 ] = 2.222;
    if (opts.count( Option::Time3 ) > 0)
        opts[ Option::Time3 ] = 3.333;
    if (opts.count( Option::Time4 ) > 0)
        opts[ Option::Time4 ] = 4.444;
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    std::map<Option, Value> opts = { { Option::Time2, 0 }, { Option::Time3, 0 } };
    foo( opts );

    // This won't work without const& opts:
    // foo( { { Option::Time2, 0 }, { Option::Time3, 0 } } );

    try {
        printf( "opts Time1 = %.3f\n", opts.at( Option::Time1 ) );
    }
    catch (std::exception& ex) {
        printf( "opts Time1 n/a\n" );
    }

    try {
        printf( "opts Time2 = %.3f\n", opts.at( Option::Time2 ) );
    }
    catch (std::exception& ex) {
        printf( "opts Time2 n/a\n" );
    }

    try {
        printf( "opts Time3 = %.3f\n", opts.at( Option::Time3 ) );
    }
    catch (std::exception& ex) {
        printf( "opts Time3 n/a\n" );
    }

    try {
        printf( "opts Time4 = %.3f\n", opts.at( Option::Time4 ) );
    }
    catch (std::exception& ex) {
        printf( "opts Time4 n/a\n" );
    }
    return 0;
}
