void foo();
void bar();

// This works as long as it is inline or template.
template <typename T>
void foofoo( T x )
{
    foo();
}

int main( int argc, char** argv )
{
    if (false) {
        foo();
    }

    if (false) {
        foofoo( 1.0 );
    }

    if constexpr (false) {
        bar();
    }

    // error: 'undef' was not declared in this scope
    // if constexpr (false) {
    //     undef();
    // }

    // error: the value of 'a' is not usable in a constant expression
    // bool a = false;
    // if constexpr (a) {
    //     bar();
    // }
}
