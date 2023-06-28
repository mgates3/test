#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void trmm()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::trmm();
}

} // namespace slate

