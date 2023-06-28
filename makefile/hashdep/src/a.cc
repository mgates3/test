#include <stdio.h>

#include "b.hh"

int zipper()
{
    printf( "%s at %s:%d\n", __func__, __FILE__, __LINE__ );
    zab();
    printf( "%s done at %s:%d\n", __func__, __FILE__, __LINE__ );
    return 0;
}
