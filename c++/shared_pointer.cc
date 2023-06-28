// Demonstrates returning a void* pointer to a std::shared_ptr,
// in order to use it inside a C interface.
// Question from Natalie Beams.

#include <memory>
#include <stdio.h>

//------------------------------------------------------------------------------
// Simply class that just prints when its constructor and destructor are called.
//
class Foo
{
public:
    Foo() {
        printf( "  %s\n", __func__ );
    }

    ~Foo() {
        printf( "  %s\n", __func__ );
    }
};

//------------------------------------------------------------------------------
// FooPtr contains a std::shared_ptr to a Foo object.
// See create2() and destroy2() for use.
//
class FooPtr
{
public:
    FooPtr( std::shared_ptr<Foo>& ptr )
        : ptr_( ptr )
    {
        printf( "  %s\n", __func__ );
    }

    ~FooPtr()
    {
        printf( "  %s\n", __func__ );
    }

    std::shared_ptr<Foo> ptr_;
};

//------------------------------------------------------------------------------
// Shows when shared_ptr goes out-of-scope, ~Foo destructor is called.
//
void simple()
{
    printf( "  %s\n", __func__ );
    std::shared_ptr<Foo> f = std::make_shared<Foo>();
    printf( "  f.get %p\n", (void*) f.get() );
    printf( "  %s done\n", __func__ );
}

//------------------------------------------------------------------------------
// Returns pointer to std::shared_ptr.
// Call destroy1() to invoke ~Foo destructor.
//
void* create1()
{
    printf( "  %s\n", __func__ );
    std::shared_ptr<Foo> f = std::make_shared<Foo>();
    printf( "  f.get %p\n", (void*) f.get() );
    
    std::shared_ptr<Foo> *fptr = new std::shared_ptr<Foo>( f );
    printf( "  fptr->get %p\n", (void*) fptr->get() );
    
    printf( "  %s done\n", __func__ );
    return fptr;
}

void destroy1( void* ptr )
{
    printf( "  %s\n", __func__ );
    std::shared_ptr<Foo> *fptr = static_cast< std::shared_ptr<Foo>* >( ptr );
    printf( "  fptr->get %p\n", (void*) fptr->get() );
    printf( "  delete fptr\n" );
    delete fptr;
    printf( "  %s done\n", __func__ );
}

//------------------------------------------------------------------------------
// Returns pointer to class FooPtr, which contains a std::shared_ptr.
// Call destroy2() to invoke ~Foo destructor.
//
void* create2()
{
    printf( "  %s\n", __func__ );
    std::shared_ptr<Foo> f = std::make_shared<Foo>();
    printf( "  f.get %p\n", (void*) f.get() );
    
    FooPtr *fooptr = new FooPtr( f );
    printf( "  fooptr->ptr_.get %p\n", (void*) fooptr->ptr_.get() );
    
    printf( "  %s done\n", __func__ );
    return fooptr;
}

void destroy2( void* ptr )
{
    printf( "  %s\n", __func__ );
    FooPtr *fooptr = static_cast< FooPtr* >( ptr );
    printf( "  fooptr->ptr_.get %p\n", (void*) fooptr->ptr_.get() );
    printf( "  delete fooptr\n" );
    delete fooptr;
    printf( "  %s done\n", __func__ );
}

//------------------------------------------------------------------------------
int main()
{
    printf( "%s\n\n", __func__ );
    
    //--------------------
    printf( "call simple\n" );
    simple();
    printf( "call simple done\n\n" );
    
    //--------------------
    printf( "call create1\n" );
    void* p1 = create1();
    printf( "call create1 done\n" );
    
    printf( "call destroy1\n" );
    destroy1( p1 );
    printf( "call destroy1 done\n\n" );
    
    //--------------------
    printf( "call create2\n" );
    void* p2 = create2();
    printf( "call create2 done\n" );
    
    printf( "call destroy2\n" );
    destroy2( p2 );
    printf( "call destroy2 done\n\n" );
    
    printf( "%s done\n", __func__ );
    return 0;
}
