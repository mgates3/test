#include <stdio.h>
#include <slate.hh>

int main( int argc, char** argv )
{
    printf( "%s\n"
            "CXX      = %s\n"
            "CXXFLAGS = %s\n"
            "LDFLAGS  = %s\n",
            __func__, slate_CXX, slate_CXXFLAGS, slate_LDFLAGS );
    slate::gemm();
    slate::hemm();
    slate::herk();
    slate::her2k();
    slate::trmm();
    slate::trsm();
    return 0;
}
