#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void gemm()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::gemm();
}

} // namespace slate

