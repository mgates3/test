// Demonstrates way to overload to_string in a namespace.
// See discussion at
// https://stackoverflow.com/questions/33399594/making-a-user-defined-class-stdto-string-able
// Adding an overload to std is _not allowed_.

#include <string>
#include <stdio.h>
#include <complex>
#include <iostream>

// Surprisingly, needs `using ::to_string` for main to find this.
template <typename T>
std::string to_string( std::complex<T> const& x )
{
    return std::to_string( std::real( x ) ) + " + "
         + std::to_string( std::imag( x ) ) + "i";
}

//------------------------------------------------------------------------------
namespace blas {

enum class Foo
{
    A, B
};

std::string to_string( Foo value )
{
    switch (value) {
        case Foo::A: return "A";
        case Foo::B: return "B";
        default: return "unknown";
    }
}

} // namespace blas

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    using std::cout;
    using std::to_string;
    using ::to_string;      // to get to_string( complex )
    //using blas::to_string;

    blas::Foo a = blas::Foo::A;
    blas::Foo b = blas::Foo::B;
    std::string x = to_string( a );
    cout << x << "\n";

    x = blas::to_string( b );
    cout << x << "\n";

    // Due to `using std::to_string`, should work w/ and w/o std::.
    x = std::to_string( 123 );
    cout << x << "\n";

    x = to_string( 123 );
    cout << x << "\n";

    x = std::to_string( 123.456 );
    cout << x << "\n";

    x = to_string( 123.456 );
    cout << x << "\n";

    // without `using ::to_string`
    x = ::to_string( std::complex<float>( 1.234, 2.456 ) );
    cout << x << "\n";

    // with `using ::to_string`
    x = to_string( std::complex<float>( 1.234, 2.456 ) );
    cout << x << "\n";

    return 0;
}
