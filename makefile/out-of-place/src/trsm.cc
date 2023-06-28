#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void trsm()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::trsm();
}

} // namespace slate

