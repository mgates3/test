// Demonstrates using >> and << operators to convert string
// to and from enum, respectively.
// This also has backwards compatibility check for whether the operators
// are defined, for use in TestSweeper.
// Cf. enum2str_to_string for function version.

#include <stdio.h>
#include <string>
#include <type_traits>

#include "get_type_name.hh"

//------------------------------------------------------------------------------
enum class Method {
    A, B, C,
};

void operator >> ( std::string const& str, Method& value )
{
    if      (str == "A") { value = Method::A; }
    else if (str == "B") { value = Method::B; }
    else if (str == "C") { value = Method::C; }
    else {
        printf( "unknown method str '%s'\n", str.c_str() );
        throw 1;
    }
}

void operator << ( std::string& str, Method value )
{
    switch (value) {
        case Method::A: str = "A"; break;
        case Method::B: str = "B"; break;
        case Method::C: str = "C"; break;
        default:
            printf( "unknown method %d\n", int( value ) );
            throw 1;
    }
}

//------------------------------------------------------------------------------
enum class Uplo {
    Upper, Lower, C,
};

void operator >> ( std::string const& str, Uplo& value )
{
    if      (str == "Upper") { value = Uplo::Upper; }
    else if (str == "Lower") { value = Uplo::Lower; }
    else {
        printf( "unknown uplo str '%s'\n", str.c_str() );
        throw 1;
    }
}

void operator << ( std::string& str, Uplo value )
{
    switch (value) {
        case Uplo::Upper: str = "Upper"; break;
        case Uplo::Lower: str = "Lower"; break;
        default:
            printf( "unknown uplo %d\n", int( value ) );
            throw 1;
    }
}

//------------------------------------------------------------------------------
enum class Target {
    X, Y, Z,
};

#ifndef NEW
#define NEW 0
#endif

#if NEW
    void operator >> ( std::string const& str, Target& value )
    {
        if      (str == "X") { value = Target::X; }
        else if (str == "Y") { value = Target::Y; }
        else if (str == "Z") { value = Target::Z; }
        else {
            printf( "unknown target str '%s'\n", str.c_str() );
            throw 1;
        }
    }

    void operator << ( std::string& str, Target value )
    {
        switch (value) {
            case Target::X: str = "X"; break;
            case Target::Y: str = "Y"; break;
            case Target::Z: str = "Z"; break;
            default:
                printf( "unknown target %d\n", int( value ) );
                throw 1;
        }
    }
#else
    // old implementation
    Target str2target( const char* str )
    {
        std::string str_ = str;
        printf( "%s\n", __func__ );
        if      (str_ == "X") { return Target::X; }
        else if (str_ == "Y") { return Target::Y; }
        else if (str_ == "Z") { return Target::Z; }
        else {
            printf( "unknown target str '%s'\n", str );
            throw 1;
        }
    }

    const char* target2str( Target value )
    {
        printf( "%s\n", __func__ );
        switch (value) {
            case Target::X: return "X"; break;
            case Target::Y: return "Y"; break;
            case Target::Z: return "Z"; break;
            default:
                printf( "unknown target %d\n", int( value ) );
                throw 1;
        }
    }
#endif

//------------------------------------------------------------------------------
/// Use SFINAE to test for existence of string >> enum input operator.
template <typename ENUM>
class has_from_string
{
    // Matches string >> enum operator; return type is void.
    template <typename T>
    static auto test( std::string s, T x )
        -> decltype( operator >> ( s, x ) );

    // Matches everything else; return type is not void.
    template <typename>
    static int test(...);

public:
    // True if string >> enum operator exists, based on void return type.
    static const bool value = std::is_same<
        void,
        decltype( test<ENUM>( std::string(), ENUM() ) )
    >::value;
};

//------------------------------------------------------------------------------
/// Use SFINAE to test for existence of string << enum output operator.
template <typename ENUM>
class has_to_string
{
    // Matches string << enum operator; return type is void.
    template <typename T>
    static auto test( std::string s, T x )
        -> decltype( operator << ( s, x ) );

    // Matches everything else; return type is not void.
    template <typename T>
    static int test(...);

public:
    // True if string >> enum operator exists, based on void return type.
    static const bool value = std::is_same<
        void,
        decltype( test<ENUM>( std::string(), ENUM() ) )
    >::value;
};

//------------------------------------------------------------------------------
template <typename ENUM>
class ParamEnum
{
public:
    typedef const char* (*enum2str)( ENUM val );
    typedef ENUM (*str2enum)( const char* str );

    //----------------------------------------
    ParamEnum( const char* name )
        : name_( name )
        , str2enum_( nullptr )
        , enum2str_( nullptr )
    {}

    //----------------------------------------
    // deprecated
    ParamEnum( const char* name, str2enum s2e, enum2str e2s )
        : name_( name )
        , str2enum_( s2e )
        , enum2str_( e2s )
    {}

    //----------------------------------------
    void parse( const char* str )
    {
        if constexpr (has_from_string<ENUM>::value) {
            // new implementation
            std::string str_ = str;
            str_ >> value_;
        }
        else if (str2enum_) {
            // old, deprecated implementation
            value_ = str2enum_( str );
        }
        else {
            printf( "unknown parse\n" );
            throw 1;
        }
    }

    //----------------------------------------
    void print()
    {
        if constexpr (has_to_string<ENUM>::value) {
            // new implementation
            std::string str;
            str << value_;
            printf( "%s = %s\n", name_.c_str(), str.c_str() );
        }
        else if (enum2str_) {
            // old, deprecated implementation
            printf( "%s = %s\n", name_.c_str(), enum2str_( value_ ) );
        }
        else {
            printf( "%s = %s\n", name_.c_str(), "unknown print" );
            throw 1;
        }
    }

protected:
    std::string name_;
    ENUM value_;

    str2enum str2enum_;
    enum2str enum2str_;
};

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    std::string s;
    Method m;
    std::string x;
    x = get_type_name< decltype( operator << ( s, m ) ) >();
    printf( "decltype %s\n", x.c_str() );

    // error: no matching function for call to 'operator<<(std::string, Method&)'
    // x = get_type_name< decltype( operator << ( std::string(), m ) ) >();
    // printf( "decltype %s\n", x.c_str() );

    #if NEW
        Target t;
        x = get_type_name< decltype( operator << ( s, t ) ) >();
        printf( "decltype %s, %lu\n", x.c_str(), 0ul );
                //sizeof( decltype( from_string( x, t ) ) );
    #endif

    printf( "\n" );

printf( "ParamEnum\n" );
    ParamEnum<Method> methodA( "method" );
    ParamEnum<Method> methodB( "method" );
    #if NEW
        ParamEnum<Target> targetX( "target" );
        ParamEnum<Target> targetY( "target" );
    #else
        ParamEnum<Target> targetX( "target", str2target, target2str );
        ParamEnum<Target> targetY( "target", str2target, target2str );
    #endif
    printf( "\n" );

    printf( "has_from_string<Method> %d\n",
            has_from_string<Method>::value );
    printf( "has_to_string<Method> %d\n",
            has_to_string<Method>::value );
    printf( "has_from_string<Target> %d\n",
            has_from_string<Target>::value );
    printf( "has_to_string<Target> %d\n",
            has_to_string<Target>::value );
    printf( "\n" );

printf( "parse method\n" );
    methodA.parse( "A" );
    methodB.parse( "B" );
printf( "parse target\n" );
    targetX.parse( "X" );
    targetY.parse( "Y" );
    printf( "\n" );

printf( "print method\n" );
    methodA.print();
    methodB.print();
printf( "print target\n" );
    targetX.print();
    targetY.print();
    printf( "\n" );

printf( "return\n" );
    return 0;
}
