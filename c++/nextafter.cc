// Test nextafter and nextforward.
// nextafter's  return type is std::common_type( from, to ).
// nexttoward's return type is same as `from`;
// `to` is promoted to long double, which doesn't really have any external effect.

#include <cmath>
#include <iomanip>
#include <iostream>

#include <omp.h>

#include "get_type_name.hh"

template <typename T>
std::string type( T x )
{
    return get_type_name<T>();
}

//------------------------------------------------------------------------------
const int cnt = 10000000;

void time_nextafter( float from, float to )
{
    double t = omp_get_wtime();
    float sum = 0;
    for (int i = 0; i < cnt; ++i) {
        float x = std::nextafter( from, to );
        sum += x;
    }
    t = (omp_get_wtime() - t) / cnt;
    printf( "nextafter ( %.2e, %.2e ) time %.4e sec, sum %.2e\n", from, to, t, sum );
}

//------------------------------------------------------------------------------
void time_nexttoward( float from, float to )
{
    double t = omp_get_wtime();
    float sum = 0;
    for (int i = 0; i < cnt; ++i) {
        float x = std::nexttoward( from, to );
        sum += x;
    }
    t = (omp_get_wtime() - t) / cnt;
    printf( "nexttoward( %.2e, %.2e ) time %.4e sec, sum %.2e\n", from, to, t, sum );
}

//------------------------------------------------------------------------------
void time_dummy( float from, float to )
{
    double t = omp_get_wtime();
    float sum = 0;
    for (int i = 0; i < cnt; ++i) {
        float x = from;
        sum += x;
    }
    t = (omp_get_wtime() - t) / cnt;
    printf( "dummy( %.2e, %.2e ) time %.4e sec, sum %.2e\n", from, to, t, sum );
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    std::cout << std::setprecision( 4 );
    std::cout << "nextafter ( from, to ) vs.\n"
              << "nexttoward( from, to )\n\n";

    float       s = std::nextafter( 0.0f, 1.0f );
    double      d = std::nextafter( 0.0,  1.0  );
    long double q = std::nextafter( 0.0L, 1.0L );
    std::cout << "float       s = " << s << '\n';
    std::cout << "double      d = " << d << '\n';
    std::cout << "long double q = " << q << "\n\n";

    std::cout << "----- `from` is float\n"; // Result type
    auto x1 = std::nextafter ( 0.0f, s );   // float
    auto y1 = std::nexttoward( 0.0f, s );   // float
    std::cout <<  "nextafter ( 0.0f, s ) = " << x1 << " " << type( x1 ) << '\n';
    std::cout <<  "nexttoward( 0.0f, s ) = " << y1 << " " << type( y1 ) << "\n\n";

    auto x2 = std::nextafter ( 0.0f, d );   // double
    auto y2 = std::nexttoward( 0.0f, d );   // float
    std::cout <<  "nextafter ( 0.0f, d ) = " << x2 << " " << type( x2 ) << '\n';
    std::cout <<  "nexttoward( 0.0f, d ) = " << y2 << " " << type( y2 ) << "\n\n";

    auto x3 = std::nextafter ( 0.0f, q );   // long double
    auto y3 = std::nexttoward( 0.0f, q );   // float
    std::cout <<  "nextafter ( 0.0f, q ) = " << x3 << " " << type( x3 ) << '\n';
    std::cout <<  "nexttoward( 0.0f, q ) = " << y3 << " " << type( y3 ) << "\n\n";

    std::cout << "----- `from` is double\n";
    auto x4 = std::nextafter ( 0.0,  s );   // double
    auto y4 = std::nexttoward( 0.0,  s );   // double
    std::cout <<  "nextafter ( 0.0,  s ) = " << x4 << " " << type( x4 ) << '\n';
    std::cout <<  "nexttoward( 0.0,  s ) = " << y4 << " " << type( y4 ) << "\n\n";

    auto x5 = std::nextafter ( 0.0,  d );   // double
    auto y5 = std::nexttoward( 0.0,  d );   // double
    std::cout <<  "nextafter ( 0.0,  d ) = " << x5 << " " << type( x5 ) << '\n';
    std::cout <<  "nexttoward( 0.0,  d ) = " << y5 << " " << type( y5 ) << "\n\n";

    auto x6 = std::nextafter ( 0.0,  q );   // long double
    auto y6 = std::nexttoward( 0.0,  q );   // double
    std::cout <<  "nextafter ( 0.0,  q ) = " << x6 << " " << type( x6 ) << '\n';
    std::cout <<  "nexttoward( 0.0,  q ) = " << y6 << " " << type( y6 ) << "\n\n";

    std::cout << "----- `from` is long double\n";
    auto x7 = std::nextafter ( 0.0L, s );   // long double
    auto y7 = std::nexttoward( 0.0L, s );   // long double
    std::cout <<  "nextafter ( 0.0L, s ) = " << x7 << " " << type( x7 ) << '\n';
    std::cout <<  "nexttoward( 0.0L, s ) = " << y7 << " " << type( y7 ) << "\n\n";

    auto x8 = std::nextafter ( 0.0L, d );   // long double
    auto y8 = std::nexttoward( 0.0L, d );   // long double
    std::cout <<  "nextafter ( 0.0L, d ) = " << x8 << " " << type( x8 ) << '\n';
    std::cout <<  "nexttoward( 0.0L, d ) = " << y8 << " " << type( y8 ) << "\n\n";

    auto x9 = std::nextafter ( 0.0L, q );   // long double
    auto y9 = std::nexttoward( 0.0L, q );   // long double
    std::cout <<  "nextafter ( 0.0L, q ) = " << x9 << " " << type( x9 ) << '\n';
    std::cout <<  "nexttoward( 0.0L, q ) = " << y9 << " " << type( y9 ) << "\n\n";

    std::cout << "--------------------\n";
    time_nextafter ( 1.0f, 2.0f );
    time_nexttoward( 1.0f, 2.0f );
    std::cout << '\n';

    time_nextafter ( 0.0f, 1.0f );
    time_nexttoward( 0.0f, 1.0f );
    std::cout << '\n';

    time_nextafter ( 0.0f, 0.0f );
    time_nexttoward( 0.0f, 0.0f );
    std::cout << '\n';

    time_nextafter ( 0.0f, s );
    time_nexttoward( 0.0f, s );
    std::cout << '\n';

    time_nextafter ( s, 1.0f );
    time_nexttoward( s, 1.0f );
    std::cout << '\n';

    float s2 = s + s;
    time_nextafter ( s, s2 );
    time_nexttoward( s, s2 );
    std::cout << '\n';

    return 0;
}
