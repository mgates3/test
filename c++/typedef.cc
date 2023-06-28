// Demonstrate that typedefs are scoped by namespace.

typedef int foo;

//------------------------------------------------------------------------------
namespace bar {

typedef int baz;

} // namespace bar

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    foo x = 0;
    bar::baz z = 0;

    #ifdef ERROR
        // error: 'baz' was not declared in this scope; did you mean 'bar::baz'?
        baz y = 0;
    #endif

    return x + z;
}
