#include <cuda_runtime_api.h>
#include <cuda.h>

#include <stdio.h>

//------------------------------------------------------------------------------
// cuGetErrorName doesn't set string if driver isn't initialized, it seems.
// This resolves that problem. It lists just a few error codes from cuda.h
//
const char* my_cuGetErrorName( CUresult err )
{
    const char* name;
    CUresult res = cuGetErrorName( err, &name );
    if (res != CUDA_SUCCESS) {
        //printf( "cuGetErrorName: %d\n", res );
        name = "cuGetErrorName error";
        switch (err) {
            case CUDA_SUCCESS:               name = "CUDA_SUCCESS"; break;
            case CUDA_ERROR_INVALID_VALUE:   name = "CUDA_ERROR_INVALID_VALUE"; break;
            case CUDA_ERROR_OUT_OF_MEMORY:   name = "CUDA_ERROR_OUT_OF_MEMORY"; break;
            case CUDA_ERROR_NOT_INITIALIZED: name = "CUDA_ERROR_NOT_INITIALIZED"; break;
        }
    }
    if (name == NULL)
        name = "(null)";
    return name;
}

//------------------------------------------------------------------------------
int main( int argc, char** argv )
{
    int version;

    // Driver-level call to get driver version.
    // #include <cuda.h> and link with -lcuda
    version = -1;
    CUresult cu_err = cuDriverGetVersion( &version );
    printf( "cuDriverGetVersion:    err %3d: %s, driver version %d (%d.%d)\n",
            cu_err, my_cuGetErrorName(cu_err),
            version, int(version/1000), int((version%1000)/10) );

    // Runtime-level calls to get driver and runtime version.
    // #include <cudart.h> and link with -lcudart
    version = -1;
    cudaError_t err = cudaDriverGetVersion( &version );
    printf( "cudaDriverGetVersion:  err %3d: %s, driver  version %d (%d.%d)\n",
            err, cudaGetErrorName(err),
            version, int(version/1000), int((version%1000)/10) );

    err = cudaSetDevice( 0 );
    printf( "cudaSetDevice( 0 ):    err %3d: %s\n",
            err, cudaGetErrorName(err) );

    version = -1;
    err = cudaRuntimeGetVersion( &version );
    printf( "cudaRuntimeGetVersion: err %3d: %s, runtime version %d (%d.%d)\n",
            err, cudaGetErrorName(err),
            version, int(version/1000),int((version%1000)/10) );

    return 0;
}
