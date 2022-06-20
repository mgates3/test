// Demonstrates using from_string and to_string functions to convert
// string to and from enum, respectively.
// This also has backwards compatibility check for whether the functions
// are defined, for use in TestSweeper.
// Cf. enum2str_operator.cc for operator version.
// Cf. enum2str_to_string.cc for non-template version that works.

#include <stdio.h>
#include <string>
#include <type_traits>

#include "get_type_name.hh"

// Can't readily overload on return type, so try using templates.
// This yields error:
//      Undefined symbols for architecture x86_64:
//        "Target from_string<Target>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)", referenced from:
//            ParamEnum<Target>::parse(char const*) in enum2str_to_string_template.o
//
// Providing a dummy implementation gets rid of the compiler error,
// but of course doesn't help the application.
template <typename T>
T from_string( std::string const& str )
#if 1
    ;
#else
    {
        // dummy implementation.
        printf( "dummy %s\n", __func__ );
        throw 1;
    }
#endif

//------------------------------------------------------------------------------
enum class Method {
    A, B, C,
};

template <>
Method from_string( std::string const& str )
{
    if      (str == "A") { return Method::A; }
    else if (str == "B") { return Method::B; }
    else if (str == "C") { return Method::C; }
    else {
        printf( "unknown method str '%s'\n", str.c_str() );
        throw 1;
    }
}

std::string to_string( Method value )
{
    switch (value) {
        case Method::A: return "A"; break;
        case Method::B: return "B"; break;
        case Method::C: return "C"; break;
        default:
            printf( "unknown method %d\n", int( value ) );
            throw 1;
    }
}

//------------------------------------------------------------------------------
enum class Uplo {
    Upper, Lower, C,
};

template <>
Uplo from_string( std::string const& str )
{
    if      (str == "Upper") { return Uplo::Upper; }
    else if (str == "Lower") { return Uplo::Lower; }
    else {
        printf( "unknown uplo str '%s'\n", str.c_str() );
        throw 1;
    }
}

std::string to_string( Uplo value )
{
    switch (value) {
        case Uplo::Upper: return "Upper"; break;
        case Uplo::Lower: return "Lower"; break;
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
    template <>
    Target from_string( std::string const& str )
    {
        if      (str == "X") { return Target::X; }
        else if (str == "Y") { return Target::Y; }
        else if (str == "Z") { return Target::Z; }
        else {
            printf( "unknown target str '%s'\n", str.c_str() );
            throw 1;
        }
    }

    std::string to_string( Target value )
    {
        switch (value) {
            case Target::X: return "X"; break;
            case Target::Y: return "Y"; break;
            case Target::Z: return "Z"; break;
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
/// Use SFINAE to test for existence of from_string( string, enum ) function.
template <typename ENUM>
class has_from_string
{
    // Matches string >> enum operator; return type is void.
    template <typename T>
    static auto test( std::string s, T x )
        -> decltype( from_string<T>( s ) );

    // Matches everything else; return type is not void.
    template <typename>
    static int test(...);

public:
    // True if string >> enum operator exists, based on void return type.
    static const bool value = std::is_same<
        ENUM,
        decltype( test<ENUM>( std::string(), ENUM() ) )
    >::value;
};

//------------------------------------------------------------------------------
/// Use SFINAE to test for existence of string = to_string( enum ) function.
template <typename ENUM>
class has_to_string
{
    // Matches string << enum operator; return type is std::string.
    template <typename T>
    static auto test( T x )
        -> decltype( to_string( x ) );

    // Matches everything else; return type is not std::string.
    template <typename T>
    static int test(...);

public:
    // True if string >> enum operator exists, based on string return type.
    static const bool value = std::is_same<
        std::string,
        decltype( test<ENUM>( ENUM() ) )
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
            value_ = from_string<ENUM>( str_ );
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
            std::string str = to_string( value_ );
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
    std::string x;
    x = get_type_name< decltype( from_string<Method>( s ) ) >();
    printf( "decltype %s\n", x.c_str() );

    #if NEW
        x = get_type_name< decltype( from_string<Target>( s ) ) >();
        printf( "decltype %s\n", x.c_str() );
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
