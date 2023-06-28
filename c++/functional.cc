// Tests giving and returning std::function from an object,
// as in SLATE's tileNb.
// Prints pointers to resulting functions to clarify when objects have
// been copied.
//
// Output:
// thyme test/c++> ./functional
// f       10,  0x7ff7bb4fa660
// a.f_    10,  0x7ff7bb4fa6e0
// a.fref_ 10,  0x7ff7bb4fa660 (same as f)
// b.f_    20,  0x7ff7bb4fa710
// b.fref  20,  0x7ff7bb4fa710
//
// fa      10,  0x7ff7bb4fa680
// far     10,  0x7ff7bb4fa6e0 (same as a.f_)
// farb    10,  0x7ff7bb4fa6e0 (same as a.f_, far)
// far2    10,  0x7ff7bb4fa6a0
// fref    10,  0x7ff7bb4fa660 (same as f, a.fref_)
// fb      20,  0x7ff7bb4fa6c0
//
// c1      10
// c2      20
// c4      10
// c6      10
// c8      10
// c7      10
// c9      10

#include <stdio.h>

#include <functional>

//------------------------------------------------------------------------------
class Foo
{
public:
    Foo( int nb )
        : f_( [nb]( int i ) { return nb; } ),
          fref_( f_ )
    {}

    Foo( std::function< int (int) >& f )
        : f_( f ),
          fref_( f )
    {}

    std::function< int (int) > get_f() { return f_; }

    // error: 'std::function<int(int)>& Foo::get_f()'
    // cannot be overloaded with 'std::function<int(int)> Foo::get_f()'
    //std::function< int (int) >& get_f() { return f_; }

    std::function< int (int) >& get_fr() { return f_; }

    std::function< int (int) >& get_fref() { return fref_; }

    // error: cannot bind rvalue reference of type
    // 'std::function<int(int)>&&' to lvalue of type 'std::function<int(int)>'
    //std::function< int (int) >&& get_fr2() { return f_; }

    std::function< int (int) > f_;
    std::function< int (int) >& fref_;
};

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    //---------
    // Construct initial objects, a from function, b from fixed nb.
    int nb = 10;
    std::function< int (int) > f = [nb]( int i ) { return nb; };
    printf( "f       %d,  %p\n", f( 0 ), (void*) &f );

    Foo a( f );
    printf( "a.f_    %d,  %p\n", a.f_( 0 ), (void*) &a.f_ );
    printf( "a.fref_ %d,  %p (same as f)\n", a.fref_( 0 ), (void*) &a.fref_ );

    nb = 20;
    Foo b( nb );
    printf( "b.f_    %d,  %p\n", b.f_( 0 ), (void*) &b.f_ );
    printf( "b.fref  %d,  %p\n", b.fref_( 0 ), (void*) &b.fref_ );
    printf( "\n" );

    //---------
    // Get functions.
    auto fa = a.get_f();
    printf( "fa      %d,  %p\n", fa( 0 ), (void*) &fa );

    // error: cannot bind non-const lvalue reference of type
    // 'std::function<int(int)>&' to an rvalue of type 'std::function<int(int)>'
    //auto& far = a.get_f();
    //printf( "far     %d\n", far( 0 ) );

    auto& far = a.get_fr();
    printf( "far     %d,  %p (same as a.f_)\n", far( 0 ), (void*) &far );

    auto&& farb = a.get_fr();
    printf( "farb    %d,  %p (same as a.f_, far)\n", farb( 0 ), (void*) &farb );

    auto&& far2 = a.get_f();
    printf( "far2    %d,  %p\n", far2( 0 ), (void*) &far2 );

    auto& fref = a.get_fref();
    printf( "fref    %d,  %p (same as f, a.fref_)\n", fref( 0 ), (void*) &fref );

    auto fb = b.get_f();
    printf( "fb      %d,  %p\n", fb( 0 ), (void*) &fb );
    printf( "\n" );

    //---------
    // Construct new objects from functions.
    Foo c1( fa );
    printf( "c1      %d\n", c1.f_( 0 ) );

    Foo c2( fb );
    printf( "c2      %d\n", c2.f_( 0 ) );

    // error: cannot bind non-const lvalue reference of type
    // 'std::function<int(int)>&' to an rvalue of type 'std::function<int(int)>'
    //Foo c3( a.get_f() );
    //printf( "c3      %d\n", c3.f_( 0 ) );

    Foo c4( a.get_fr() );
    printf( "c4      %d\n", c4.f_( 0 ) );

    Foo c6( far );
    printf( "c6      %d\n", c6.f_( 0 ) );

    Foo c8( farb );
    printf( "c8      %d\n", c8.f_( 0 ) );

    Foo c7( far2 );
    printf( "c7      %d\n", c7.f_( 0 ) );

    Foo c9( fref );
    printf( "c9      %d\n", c9.f_( 0 ) );

    return 0;
}
