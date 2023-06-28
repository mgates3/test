#include <stdio.h>

#if NO_DEPRECATED
    #pragma message "NO_DEPRECATED"
    #define LAPACK_DEPRECATED(msg)

#elif __cplusplus >= 201402 // C++14
    #pragma message "[[deprecated]]"
    #define LAPACK_DEPRECATED(msg) [[deprecated(msg)]]

#elif defined(_MSC_VER)
    #pragma message "__declspec"
    #define LAPACK_DEPRECATED(msg) __declspec(deprecated(msg))

#elif defined(__GNUC__)
    #pragma message "__attribute__"
    #define LAPACK_DEPRECATED(msg) __attribute__((deprecated(msg)))

#else
    #pragma message "none"
    #define LAPACK_DEPRECATED(msg)
#endif

//------------------------------------------------------------------------------
typedef enum LAPACK_DEPRECATED("baz1 replaced with zab1") baz1 {
    baz1_a,
    baz1_b
} baz1;

enum class LAPACK_DEPRECATED("baz2 replaced with zab2") baz2 {
    a,
    b
};

enum class baz3 {
    a,
    b
};

LAPACK_DEPRECATED("bz3 replaced with baz3")
typedef baz3 bz3;

// warning: attribute ignored in declaration of 'enum baz3' [-Wattributes]
// note: attribute for 'enum baz3' must follow the 'enum' keyword
// LAPACK_DEPRECATED enum baz3 {
//     baz3_a,
//     baz3_b
// };
//
// LAPACK_DEPRECATED enum class baz4 {
//     baz4_a,
//     baz4_b
// };

// error: use of enum 'baz3' without previous declaration
// enum baz3 LAPACK_DEPRECATED {
//     baz3_a,
//     baz3_b
// };
//
// enum class baz4 LAPACK_DEPRECATED {
//     baz4_a,
//     baz4_b
// };

//------------------------------------------------------------------------------
LAPACK_DEPRECATED("foo1 replaced by bar1")
void foo1(double x);

void foo1(double x)
{
    printf( "%s\n", __func__ );
}

LAPACK_DEPRECATED("foo2 replaced by bar2")
inline void foo2(double x)
{
    printf( "%s\n", __func__ );
}

template <typename T>
LAPACK_DEPRECATED("foo3 replaced by bar3")
void foo3(T x)
{
    printf( "%s\n", __func__ );
}

// error: expected unqualified-id before 'template'
// LAPACK_DEPRECATED
// template <typename T>
// void foo4(T x)
// {
//     printf( "%s\n", __func__ );
// }

//------------------------------------------------------------------------------
int main()
{
    double x = 1;
    baz1 a = baz1_a;
    baz2 b = baz2::b;
    bz3  c = bz3::b;
    foo1( x );
    foo2( x );
    foo3( x );
    return 0;
}
