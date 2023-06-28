#include <complex>
#include <type_traits>

// With ::type
template < typename T, typename = typename std::enable_if< std::is_trivial<T>::value >::type >
class Foo1
{
};

// With enable_if_t, should work with C++14.
template < typename T, typename = typename std::enable_if_t< std::is_trivial<T>::value > >
class Foo2
{
};

// Accidentally omits ::type, doesn't generate desired errors.
template < typename T, typename = typename std::enable_if< std::is_trivial<T>::value > >
class Foo3
{
};

// Dummy class that is not trivial, because it has a constructor.
class Dummy
{
    Dummy() {}
    ~Dummy() {}
};

int main( int argc, char** argv )
{
    Foo1<int> i1;
    Foo2<int> i2;
    Foo3<int> i3;
    Foo1<double> d1;
    Foo2<double> d2;
    Foo3<double> d3;

    // These give desired errors:
    // error: no type named 'type' in 'struct std::enable_if<false, void>'
    #ifdef ERROR
        Foo1< std::complex<double> > c1;
        Foo2< std::complex<double> > c2;

        Foo1< Dummy > z1;
        Foo2< Dummy > z2;

        // unused
        (void) c1;
        (void) c2;
        (void) z1;
        (void) z2;
    #endif

    // These do not give desired errors.
    Foo3< std::complex<double> > c3;
    Foo3< Dummy > z3;

    // unused
    (void) i1;
    (void) i2;
    (void) i3;
    (void) d1;
    (void) d2;
    (void) d3;
    (void) c3;
    (void) z3;

    return 0;
}
