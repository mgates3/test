#include <stdio.h>
#include <algorithm>
#include <vector>

//------------------------------------------------------------------------------
class Queue
{
public:
    Queue( int dev ):
        dev_( dev ),
        id_( s_id++ )
    { printf( "%s( %d ) id %d\n", __func__, dev_, id_ ); }

   ~Queue()
    { printf( "%s( %d ) id %d\n", __func__, dev_, id_ ); }

    // not copyable
    Queue( Queue const& orig ) = delete;
    Queue& operator=( Queue const& orig ) = delete;

    // not moveable
    // Queue( Queue&& orig ) = delete;

    // moveable
    Queue( Queue&& orig )
    {
        printf( "move %d/%d => %d/%d\n", dev_, id_, orig.dev_, orig.id_ );
        std::swap( dev_, orig.dev_ );
        std::swap( id_, orig.id_ );
    }

    //Queue& operator=( Queue&& orig ) = delete;
    Queue& operator=( Queue&& orig )
    {
        printf( "assign %d/%d => %d/%d\n", dev_, id_, orig.dev_, orig.id_ );
        std::swap( dev_, orig.dev_ );
        std::swap( id_, orig.id_ );
        return *this;
    }

    int dev() const { return dev_; }
    int id()  const { return id_; }

protected:
    int dev_;
    int id_;
    static int s_id;
};

int Queue::s_id = 0;

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    std::vector< Queue > queues;
    queues.reserve( 4 );
    queues.emplace_back( 1 );
    queues.emplace_back( 3 );
    queues.emplace_back( 5 );
    queues.emplace_back( 7 );

    //queues[0] = Queue( 4 );

    for (int i = 0; i < 4; ++i ) {
        printf( "queues[%d] dev %d, id %d\n", i, queues[i].dev(), queues[i].id() );
    }

    // Queue  q1 = queues[0];  // error: use of deleted function 'Queue::Queue(const Queue&)'
    // auto   q2 = queues[0];  // error: use of deleted function 'Queue::Queue(const Queue&)'
    Queue& q3 = queues[0];
    auto&  q4 = queues[0];
    Queue q5( 9 );
    q5 = std::move( queues[0] );
    // q5 = queues[0];

    printf( "done\n" );

    return 0;
}
