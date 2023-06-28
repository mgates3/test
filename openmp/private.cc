#include <omp.h>
#include <stdio.h>
#include <unistd.h>

#include <string>

//------------------------------------------------------------------------------
class block
{
public:
    static int s_nest;
    #pragma omp threadprivate( s_nest )

    block( const char* msg ):
        nest_( s_nest++ ),
        msg_( msg )
    {
        int tid = omp_get_thread_num();
        printf( "    tid %2d, %s, nest %d\n", tid, msg_.c_str(), nest_ );
    }

    ~block()
    {
        s_nest--;
        int tid = omp_get_thread_num();
        printf( "    tid %2d, %s, nest %d done\n", tid, msg_.c_str(), nest_ );
    }

    int nest_;
    std::string msg_;
};

int block::s_nest = 1;

//------------------------------------------------------------------------------
void thread_main()
{
    int tid = omp_get_thread_num();
    printf( "tid %2d, %s\n", tid, __func__ );
    {
        block x( "one" );
        block y( "two" );
        usleep( 500 );
    }
    {
        block x( "one" );
        block y( "two" );
        block z( "three" );
        usleep( 500 );
    }
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    #pragma omp parallel for
    for (int i = 0; i < 5; ++i) {
        thread_main();
    }

    return 0;
}
