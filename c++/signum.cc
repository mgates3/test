#include <stdio.h>
#include <stdint.h>

//------------------------------------------------------------------------------
/// Sign (signum) function.
/// @return -1 if val <  0,
///          0 if val == 0,
///         +1 if val >  0.
template <typename real_t> real_t sign( real_t val )
{
    return (real_t(0) < val) - (val < real_t(0));
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    using llong = long long;

    for (int i = -3; i <= 3; ++i) {
        printf( "sign( %5d ) = %5d  int\n", i, sign( i ) );
    }
    for (int64_t i = -3; i <= 3; ++i) {
        printf( "sign( %5lld ) = %5lld  int64_t\n", llong( i ), llong( sign( i ) ) );
    }
    for (float i = -3; i <= 3; ++i) {
        printf( "sign( %5.2f ) = %5.2f  float\n", i, sign( i ) );
    }
    for (double i = -3; i <= 3; ++i) {
        printf( "sign( %5.2f ) = %5.2f  double\n", i, sign( i ) );
    }
}
