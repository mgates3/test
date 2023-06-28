// Demonstrate pragmas to ignore deprecated calls inside deprecated functions.
// See https://stackoverflow.com/questions/13459602/how-can-i-get-rid-of-deprecated-warnings-in-deprecated-functions-in-gcc

class Parent
{
public:
    Parent() {}

    [[deprecated]]
    Parent( int x ) {}
};

class Child: public Parent
{
public:
    Child():
        Parent()
    {}

    // pragmas make gcc ignore Child's use of deprecated Parent( int ).
    // clang already ignores it.
    // Without this, g++ prints:
    // deprecated2.cc: In constructor 'Child::Child(int)':
    // deprecated2.cc:29:19: warning: 'Parent::Parent(int)' is deprecated [-Wdeprecated-declarations]
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    [[deprecated]]
    Child( int x ):
        Parent( x )  // don't want warning here
    {}
    #pragma GCC diagnostic pop
};

int main( int argc, char** argv )
{
    Parent a;
    Child x;

    Parent b( 100 );  // generates warning
    Child y( 100 );   // generates warning

    return 0;
}
