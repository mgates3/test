// Demonstrates overloading to call the same function for different types.
// E.g. blas::gemm calls sgemm, dgemm, cgemm, zgemm depending on the type.

//------------------------------------------------------------------------------
// Dummy stuff. Real stuff defined by fftw.
typedef float fftwf_plan;
typedef double fftw_plan;

fftwf_plan fftwf_plan_many_dft( float* x ) { return 0; }
fftw_plan fftw_plan_many_dft( double* x ) { return 0; }

//------------------------------------------------------------------------------
// Overloaded wrapper for float, with same name as double function.
// Using auto as return type requires C++14. Otherwise use fftwf_plan.
//
auto fftw_plan_many_dft( float* x)
{
    return fftwf_plan_many_dft( x );
}

//------------------------------------------------------------------------------
// Alternatively, make 2 wrappers with a new name:
//
fftwf_plan fftw_plan_many_dft_wrapper( float* x )
{
    return fftwf_plan_many_dft( x );
}

fftw_plan fftw_plan_many_dft_wrapper( double* x )
{
    return fftw_plan_many_dft( x );
}

//------------------------------------------------------------------------------
template <typename T>
class FFT3d
{
public:
    void setup_ffts()
    {
        // using real_t = blas::real_type<T>;
        // nearly same as:
        // typedef blas::real_type<T> real_t;
    
        T* dummy = nullptr;
        plan_forward = fftw_plan_many_dft( dummy );
      
        // Alternatively:
        plan_forward = fftw_plan_many_dft_wrapper( dummy );
        
        // Nope, this syntax doesn't work, because fftw_plan_many_dft_wrapper
        // isn't templated, it's overloaded.
        // plan_forward = fftw_plan_many_dft_wrapper<T>( nullptr );
    }
    
    double plan_forward;  // dummy; use traits for type.
};

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    FFT3d<float> s;
    s.setup_ffts();
    
    FFT3d<float> d;
    d.setup_ffts();
    
    return 0;
}
