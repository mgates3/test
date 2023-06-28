#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void herk()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::herk();
}

} // namespace slate

