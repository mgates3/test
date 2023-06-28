// Demonstrates using C++ traits to choose between different fftw plan types,
// based on the precision type.

#include <stdio.h>

//------------------------------------------------------------------------------
// Stubs that would be defined by FFTW.
struct fftwf_plan
{
    float x;
};

struct fftw_plan
{
    double x;
};

//------------------------------------------------------------------------------
// Traits to lookup FFTW plan type. Default is double.
template <typename T>
struct fftw_traits
{
    typedef fftw_plan plan_type;
};

// Specialization for float.
template <>
struct fftw_traits<float>
{
    typedef fftwf_plan plan_type;
};

//------------------------------------------------------------------------------
template <typename T>
class FFT3d
{
public:
    typename fftw_traits<T>::plan_type plan_forward;
    typename fftw_traits<T>::plan_type plan_backward;
};

//------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    fftw_traits<float>::plan_type ys;
    fftw_traits<double>::plan_type yd;
    
    printf( "ys: sizeof %lu\n", sizeof(ys.x) );
    printf( "yd: sizeof %lu\n", sizeof(yd.x) );
    
    FFT3d<float> s;
    FFT3d<double> d;
    
    printf( "s:  sizeof %lu\n", sizeof(s.plan_forward.x) );
    printf( "d:  sizeof %lu\n", sizeof(d.plan_forward.x) );
    
    return 0;
}
