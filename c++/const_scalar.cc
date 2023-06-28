// Tests whether prototypes need const on scalars.
// It seems they don't -- it has no effect on the mangled name:
// thyme test/c++> nm const_scalar | c++filt
// 0000000100003f70 T bar(int)
// 0000000100003f60 T foo(int)
// 0000000100000000 T __mh_execute_header
// 0000000100003f80 S _main
//                  U dyld_stub_binder


int foo( int const n );

int foo( int const n )
{
    return n;
}

int bar( int n );

int bar( int const n )
{
    // n = 2;  // error
    return n;
}

int main()
{
    int n1 = 1;
    int n2 = foo( n1 );
    int n3 = bar( n1 );

    const int n = 1;
    // n = 2;  // error

}
