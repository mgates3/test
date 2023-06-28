#include <stdio.h>

#include <algorithm>
#include <vector>

const int fork_size = 4;

struct stream_struct;
struct handle_struct;

typedef stream_struct* stream_t;
typedef handle_struct* handle_t;

//------------------------------------------------------------------------------
class Queue
{
public:
    //--------------------
    Queue() = delete;
    //     : device_( -1 )
    // {
    //     for (int i = 0; i < fork_size; ++i) {
    //         events_[ i ] = -1;
    //     }
    //     printf( "%-10s      default, events = [ ", __func__ );
    //     for (int i = 0; i < fork_size; ++i) {
    //         printf( " %4p", events_[ i ] );
    //     }
    //     printf( " ]\n" );
    // }

    #ifdef ERROR
        //--------------------
        Queue( int device, int64_t batch_size = 0 )
            : device_( device )
        {
            printf( "%s regular, int64_t\n", __func__ );
        }
    #else
        //--------------------
        Queue( int device, int batch_size = 0 )
        {
            printf( "%s regular, int\n", __func__ );

            // Fill in some dummy values for events pointers.
            for (int i = 0; i < fork_size; ++i) {
                events_[ i ] = (int*) int64_t( device * 10 + i );
            }
            printf( "%-10s      dev=%3d, events = [ ", __func__, device_ );
            for (int i = 0; i < fork_size; ++i) {
                printf( " %4p", (void*) events_[ i ] );
            }
            printf( " ]\n" );
        }
    #endif

    //--------------------
    Queue( int device, stream_t stream, int64_t batch_size = 0 )
    {
        printf( "%s stream\n", __func__ );
    }

    //--------------------
    Queue( int device, handle_t handle, int64_t batch_size = 0 )
    {
        printf( "%s handle\n", __func__ );
    }

    //--------------------
    ~Queue()
    {
        printf( "%-10s      dev=%3d, events = [ ", __func__, device_ );
        for (int i = 0; i < fork_size; ++i) {
            printf( " %4p", (void*) events_[ i ] );
        }
        printf( " ]\n" );
    }

    //--------------------
    Queue( Queue const& orig ) = delete;
    // {
    //     device_ = orig.device_;
    //     printf( "%-10s copy dev=%3d, events = [ ", __func__, device_ );
    //     for (int i = 0; i < fork_size; ++i) {
    //         printf( " %4p", (void*) events_[ i ] );
    //     }
    //     printf( " ]; " );
    //     printf( ", orig.dev=%3d, events = [ ", orig.device_ );
    //     for (int i = 0; i < fork_size; ++i) {
    //         printf( " %4p", (void*) orig.events_[ i ] );
    //     }
    //     printf( " ]\n" );
    // }

    //--------------------
    Queue& operator = ( Queue const& orig ) = delete;
    // {
    //     device_ = orig.device_;
    //     printf( "%-10s copy dev=%3d, events = [ ", __func__, device_ );
    //     for (int i = 0; i < fork_size; ++i) {
    //         printf( " %4p", (void*) events_[ i ] );
    //     }
    //     printf( " ]; " );
    //     printf( ", orig.dev=%3d, events = [ ", orig.device_ );
    //     for (int i = 0; i < fork_size; ++i) {
    //         printf( " %4p", (void*) orig.events_[ i ] );
    //     }
    //     printf( " ]\n" );
    //     return *this;
    // }

    //--------------------
    Queue( Queue&& orig )
        : device_( -1 )
        , events_{ nullptr } // Sets whole array to nullptr (0).
    {
        std::swap( device_, orig.device_ );
        std::swap( events_, orig.events_ );
        printf( "%-10s move dev=%3d, events = [ ", __func__, device_ );
        for (int i = 0; i < fork_size; ++i) {
            printf( " %4p", (void*) events_[ i ] );
        }
        printf( " ]; " );
        printf( ", orig.dev=%3d, events = [ ", orig.device_ );
        for (int i = 0; i < fork_size; ++i) {
            printf( " %4p", (void*) orig.events_[ i ] );
        }
        printf( " ]\n" );
    }

    //--------------------
    Queue& operator = ( Queue&& orig )
    {
        std::swap( device_, orig.device_ );
        std::swap( events_, orig.events_ );
        printf( "%-10s move dev=%3d, events = [ ", __func__, device_ );
        for (int i = 0; i < fork_size; ++i) {
            printf( " %4p", (void*) events_[ i ] );
        }
        printf( " ]; " );
        printf( ", orig.dev=%3d, events = [ ", orig.device_ );
        for (int i = 0; i < fork_size; ++i) {
            printf( " %4p", (void*) orig.events_[ i ] );
        }
        printf( " ]\n" );
        return *this;
    }

    int device_;
    int* events_[ fork_size ];
};

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    printf( "%-10s\n", __func__ );

    int dev = 0;
    stream_t stream;
    handle_t handle;

    int     size_int = 0;
    int64_t size_i64 = 0;

    Queue q1a( dev );
    Queue q1b( dev, 0 );
    Queue q1c( dev, 1000 );
    Queue q1d( dev, size_int );
    Queue q1e( dev, size_i64 );

    #ifdef ERROR
        // With Queue( int, int64_t ), this becomes ambiguous.
        // It has to promote 0 to something, and doesn't know whether to
        // promote to int64_t or to a pointer.
        // error: call of overloaded 'Queue(int&, int)' is ambiguous
        Queue q1x( dev, 0 );

        // Explicitly casting to int64 resolves the ambiguity.
        Queue q1y( dev, int64_t( 0 ) );
    #endif

    #ifdef ERROR
        // error: call of overloaded 'Queue(int&, std::nullptr_t)' is ambiguous
        Queue q2a( dev, nullptr );

        // error: call of overloaded 'Queue(int&, std::nullptr_t, int)' is ambiguous
        Queue q2b( dev, nullptr, 0 );

        // error: call of overloaded 'Queue(int&, std::nullptr_t, int)' is ambiguous
        Queue q2c( dev, nullptr, 1000 );
    #endif

    Queue q3a( dev, stream );
    Queue q3b( dev, stream, 0 );
    Queue q3c( dev, stream, 1000 );
    Queue q3d( dev, stream, size_int );
    Queue q3e( dev, stream, size_i64 );

    Queue q4a( dev, handle );
    Queue q4b( dev, handle, 0 );
    Queue q4c( dev, handle, 1000 );
    Queue q4d( dev, handle, size_int );
    Queue q4e( dev, handle, size_i64 );

    /*
    printf( "\n%-10s: Queue q( dev )\n", __func__ );
    int dev = 0;
    Queue q( dev );

    printf( "\n%-10s: Queue q2( dev )\n", __func__ );
    Queue q2( 2 );
    // q = q2;          // error: use of deleted function 'Queue& Queue::operator=(const Queue&)'
    // Queue q3( q2 );  // error: use of deleted function 'Queue::Queue(const Queue&)'

    int nq = 5;
    printf( "\n%-10s: vector<Queue> qs( nq=%d )\n", __func__, nq );

    // error: use of deleted function 'Queue::Queue()'
    //std::vector<Queue> qs( nq );

    std::vector<Queue> qs;

    for (int i = 0; i < nq; ++i) {
        printf( "\n%-10s: Queue qs( nq=%d )\n", __func__, nq );
        //qs[ i ] = Queue( 10 + i );
        qs.push_back( Queue( 10 + i ) );
    }

    // This actually calls Queue( dev ) constructor because of optimizations,
    // not the Queue( Queue&& ) move constructor.
    printf( "\n%-10s: Queue( Queue )\n", __func__ );
    Queue q4{ Queue( 20 ) };

    // This will call move constructor, possibly for all elements if it
    // has to resize vector.
    printf( "\n%-10s: vector<Queue> qs;\n", __func__ );
    std::vector<Queue> queues;

    printf( "\n%-10s: queues.push_back( Queue )\n", __func__ );
    queues.push_back( Queue( 30 ) );
    */

    printf( "\n%-10s done\n", __func__ );
    return 0;
}
