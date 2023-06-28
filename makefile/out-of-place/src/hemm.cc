#include <blas.hh>
#include <slate_config.hh>

#include <stdio.h>

namespace slate {

void hemm()
{
    printf( "slate::%s\n", __func__ );
    printf( "    " );
    blas::hemm();
}

} // namespace slate

