#include <stdio.h>

int zab()
{
    printf( "%s at %s:%d\n", __func__, __FILE__, __LINE__ );
    return 0;
}
