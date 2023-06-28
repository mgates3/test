// Tests how integers are returned, which is modulo 256.
//
// > ./exit_code -1 ; echo $?
// status -1
// 255
// > ./exit_code 1 ; echo $?
// status 1
// 1
// > ./exit_code 255 ; echo $?
// status 255
// 255
// > ./exit_code 256 ; echo $?
// status 256
// 0
// > ./exit_code 512 ; echo $?
// status 512
// 0
// > ./exit_code 511 ; echo $?
// status 511
// 255

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char** argv )
{
    int status = 0;
    if (argc > 1)
        status = atoi( argv[ 1 ] );
    printf( "status %d\n", status );
    return status;
}
