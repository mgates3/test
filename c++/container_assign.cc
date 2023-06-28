// Demonstrate that trailing comma is okay in assigning to a container:
// plain array, map, vector, etc.

#include <map>
#include <vector>

#include <assert.h>

//------------------------------------------------------------------------------
enum class Option
{
    Target,
    Lookahead,
    BlockSize,
    Tolerance,
};

//------------------------------------------------------------------------------
class OptionValue
{
public:
    OptionValue( int x ): x_( x ) {}
    int x_;
};

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    //----- map
    std::map< Option, OptionValue > opts1 = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 },   // trailing comma ok
    };
    assert( opts1.size() == 2 );

    std::map< Option, OptionValue > opts2 = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 }    // no trailing comma ok
    };
    assert( opts2.size() == 2 );

    //----- vector
    std::vector< std::pair< Option, OptionValue > > opts3 = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 },   // trailing comma ok
    };
    assert( opts3.size() == 2 );

    std::vector< std::pair< Option, OptionValue > > opts4 = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 }    // no trailing comma ok
    };
    assert( opts4.size() == 2 );

    //----- plain array
    std::pair< Option, OptionValue > opts5[] = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 },   // trailing comma ok
    };
    assert( sizeof( opts5 ) / sizeof( std::pair< Option, OptionValue > ) == 2 );

    std::pair< Option, OptionValue > opts6[] = {
        { Option::Target,    1 },
        { Option::Lookahead, 2 }    // no trailing comma ok
    };
    assert( sizeof( opts6 ) / sizeof( std::pair< Option, OptionValue > ) == 2 );

    return 0;
}
