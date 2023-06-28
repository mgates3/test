#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void her2k()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::her2k();
}

} // namespace slate

