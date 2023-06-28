#include <thrust/device_vector.h>
#include <thrust/complex.h>
#include <complex>
#include <vector>

int main( int argc, char** argv )
{
    std::vector< std::complex<double> > x( 10 );
    
    thrust::device_vector< std::complex<double> > dx;
    dx = x;
    
    thrust::device_vector< thrust::complex<double> > dx2;
    dx = x;
    
    return 0;
}
