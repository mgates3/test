#include <mpi.h>
#include <stdio.h>

int main( int argc, char** argv )
{
    char buf[ MPI_MAX_LIBRARY_VERSION_STRING ];
    int len;
    MPI_Get_library_version( buf, &len );
    printf( "MPI_Get_library_version = %s, len %d\n", buf, len );
    return 0;
}
