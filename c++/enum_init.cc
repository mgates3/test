// Tests initializing enums from other enums.
// In enum C, using values from enum A out-of-order results in duplicate values,
// which is probably not desired.
//
// test/c++> ./enum_init
// A 1, 2, 3
// B 1, 2, 3, 4, 5
// C 1, 2, 3, 2, 3

#include <stdio.h>

enum class A {
    a = 1,  // == 1
    b,      // == 2
    c,      // == 3
};

enum class B {
    aa = int( A::a ),   // == 1
    bb = int( A::b ),   // == 2
    cc = int( A::c ),   // == 3
    dd,
    ee,
};

enum class C {
    bb = int( A::b ),   // == 2
    cc = int( A::c ),   // == 3
    aa = int( A::a ),   // == 1
    dd,                 // == 2, same as bb
    ee,                 // == 3, same as cc
};

int main( int argc, char** argv )
{
    printf( "A %d, %d, %d\n",
            int( A::a ), int( A::b ), int( A::c ) );

    printf( "B %d, %d, %d, %d, %d\n",
            int( B::aa ), int( B::bb ), int( B::cc ), int( B::dd ), int( B::ee ) );

    printf( "C %d, %d, %d, %d, %d\n",
            int( C::aa ), int( C::bb ), int( C::cc ), int( C::dd ), int( C::ee ) );

    return 0;
}
