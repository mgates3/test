#include <stdio.h>

#include "a.hh"

int main( int argc, char** argv )
{
    printf( "%s at %s:%d\n", __func__, __FILE__, __LINE__ );
    zipper();
    printf( "%s done at %s:%d\n", __func__, __FILE__, __LINE__ );
    return 0;
}
