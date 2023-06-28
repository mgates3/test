#include <stdio.h>
#include <stdexcept>
#include <string>

#include <cuda_runtime.h>

#define throw_cuda_error( err ) \
    do { \
        cudaError_t err_ = (err); \
        if (err_ != cudaSuccess) { \
            throw std::runtime_error( std::string( "CUDA error at " ) \
                                      + __FILE__ + ":" \
                                      + std::to_string(__LINE__) + ": " \
                                      + cudaGetErrorString( err_ ) ); \
        } \
    } while(0)

int main()
{
    try {
        int cnt;
        throw_cuda_error(
            cudaGetDeviceCount( &cnt ));
        printf( "device count %d\n", cnt );
        for (int dev = 0; dev < cnt; ++dev) {
            printf( "--------------------------------------------------------------------------------\n" );
            printf( "device                            %d\n", dev );

            cudaDeviceProp prop;
            throw_cuda_error(
                cudaGetDeviceProperties( &prop, dev ));

            printf( "name                              %s\n",  // char[256]
                prop.name );
            //printf( "uuid                              ???\n" );
            printf( "totalGlobalMem                    %.2f GiB (%lu)\n", // size_t
                prop.totalGlobalMem / (1024.*1024*1024),
                prop.totalGlobalMem );
            printf( "sharedMemPerBlock                 %.0f KiB (%lu)\n", // size_t
                prop.sharedMemPerBlock / 1024.,
                prop.sharedMemPerBlock );
            printf( "regsPerBlock                      %d\n",  // int
                prop.regsPerBlock );
            printf( "warpSize                          %d\n",  // int
                prop.warpSize );
            printf( "memPitch                          %lu\n", // size_t
                prop.memPitch );
            printf( "maxThreadsPerBlock                %d\n",  // int
                prop.maxThreadsPerBlock );
            printf( "maxThreadsDim                     %d, %d, %d\n",  // int[3]
                prop.maxThreadsDim[0],
                prop.maxThreadsDim[1],
                prop.maxThreadsDim[2] );
            printf( "maxGridSize                       %d, %d, %d\n",  // int[3]
                prop.maxGridSize[0],
                prop.maxGridSize[1],
                prop.maxGridSize[2] );
            printf( "clockRate                         %.0f MHz (%d KHz)\n",  // int
                prop.clockRate / 1000.,
                prop.clockRate );
            printf( "totalConstMem                     %.0f KiB (%lu)\n", // size_t
                prop.totalConstMem / 1024.,
                prop.totalConstMem );
            printf( "major                             %d\n",  // int
                prop.major );
            printf( "minor                             %d\n",  // int
                prop.minor );
            printf( "textureAlignment                  %lu\n", // size_t
                prop.textureAlignment );
            printf( "texturePitchAlignment             %lu\n", // size_t
                prop.texturePitchAlignment );
            printf( "deviceOverlap                     %d\n",  // int
                prop.deviceOverlap );
            printf( "multiProcessorCount               %d\n",  // int
                prop.multiProcessorCount );
            printf( "kernelExecTimeoutEnabled          %d\n",  // int
                prop.kernelExecTimeoutEnabled );
            printf( "integrated                        %d\n",  // int
                prop.integrated );
            printf( "canMapHostMemory                  %d\n",  // int
                prop.canMapHostMemory );
            printf( "computeMode                       %d\n",  // int
                prop.computeMode );
            printf( "maxTexture1D                      %d\n",  // int
                prop.maxTexture1D );
            printf( "maxTexture1DMipmap                %d\n",  // int
                prop.maxTexture1DMipmap );
            printf( "maxTexture1DLinear                %d\n",  // int
                prop.maxTexture1DLinear );
            printf( "maxTexture2D                      %d, %d\n", // int[2]
                prop.maxTexture2D[0],
                prop.maxTexture2D[1] );
            printf( "maxTexture2DMipmap                %d, %d\n", // int[2]
                prop.maxTexture2DMipmap[0],
                prop.maxTexture2DMipmap[1] );
            printf( "maxTexture2DGather                %d, %d\n", // int[2]
                prop.maxTexture2DGather[0],
                prop.maxTexture2DGather[1] );
            printf( "maxTexture2DLinear                %d, %d, %d\n", // int[3]
                prop.maxTexture2DLinear[0],
                prop.maxTexture2DLinear[1],
                prop.maxTexture2DLinear[2] );
            printf( "maxTexture3D                      %d, %d, %d\n", // int[3]
                prop.maxTexture3D[0],
                prop.maxTexture3D[1],
                prop.maxTexture3D[2] );
            printf( "maxTexture3DAlt                   %d, %d, %d\n", // int[3]
                prop.maxTexture3DAlt[0],
                prop.maxTexture3DAlt[1],
                prop.maxTexture3DAlt[2] );
            printf( "maxTextureCubemap                 %d\n",  // int
                prop.maxTextureCubemap );
            printf( "maxTexture1DLayered               %d, %d\n",  // int[2]
                prop.maxTexture1DLayered[0],
                prop.maxTexture1DLayered[1] );
            printf( "maxTexture2DLayered               %d, %d, %d\n",  // int[3]
                prop.maxTexture2DLayered[0],
                prop.maxTexture2DLayered[1],
                prop.maxTexture2DLayered[2] );
            printf( "maxTextureCubemapLayered          %d, %d\n",  // int[2]
                prop.maxTextureCubemapLayered[0],
                prop.maxTextureCubemapLayered[1] );
            printf( "maxSurface1D                      %d\n",  // int
                prop.maxSurface1D );
            printf( "maxSurface2D                      %d, %d\n",  // int[2]
                prop.maxSurface2D[0],
                prop.maxSurface2D[1] );
            printf( "maxSurface3D                      %d, %d, %d\n",  // int[3]
                prop.maxSurface3D[0],
                prop.maxSurface3D[1],
                prop.maxSurface3D[2] );
            printf( "maxSurface1DLayered               %d, %d\n",  // int[2]
                prop.maxSurface1DLayered[0],
                prop.maxSurface1DLayered[1] );
            printf( "maxSurface2DLayered               %d, %d, %d\n",  // int[3]
                prop.maxSurface2DLayered[0],
                prop.maxSurface2DLayered[1],
                prop.maxSurface2DLayered[2] );
            printf( "maxSurfaceCubemap                 %d\n",  // int
                prop.maxSurfaceCubemap );
            printf( "maxSurfaceCubemapLayered          %d, %d\n",  // int[2]
                prop.maxSurfaceCubemapLayered[0],
                prop.maxSurfaceCubemapLayered[1] );
            printf( "surfaceAlignment                  %lu\n", // size_t
                prop.surfaceAlignment );
            printf( "concurrentKernels                 %d\n",  // int
                prop.concurrentKernels );
            printf( "ECCEnabled                        %d\n",  // int
                prop.ECCEnabled );
            printf( "pciBusID                          %d\n",  // int
                prop.pciBusID );
            printf( "pciDeviceID                       %d\n",  // int
                prop.pciDeviceID );
            printf( "pciDomainID                       %d\n",  // int
                prop.pciDomainID );
            printf( "tccDriver                         %d\n",  // int
                prop.tccDriver );
            printf( "asyncEngineCount                  %d\n",  // int
                prop.asyncEngineCount );
            printf( "unifiedAddressing                 %d\n",  // int
                prop.unifiedAddressing );
            printf( "memoryClockRate                   %.0f MHz (%d KHz)\n",  // int
                prop.memoryClockRate / 1000.,
                prop.memoryClockRate );
            printf( "memoryBusWidth                    %d\n",  // int
                prop.memoryBusWidth );
            printf( "l2CacheSize                       %.2f MiB (%d)\n",  // int
                prop.l2CacheSize / (1024.*1024),
                prop.l2CacheSize );
            printf( "maxThreadsPerMultiProcessor       %d\n",  // int
                prop.maxThreadsPerMultiProcessor );
            printf( "streamPrioritiesSupported         %d\n",  // int
                prop.streamPrioritiesSupported );
            printf( "globalL1CacheSupported            %d\n",  // int
                prop.globalL1CacheSupported );
            printf( "localL1CacheSupported             %d\n",  // int
                prop.localL1CacheSupported );
            printf( "sharedMemPerMultiprocessor        %.0f KiB (%lu)\n", // size_t
                prop.sharedMemPerMultiprocessor / 1024.,
                prop.sharedMemPerMultiprocessor );
            printf( "regsPerMultiprocessor             %d\n",  // int
                prop.regsPerMultiprocessor );
            printf( "managedMemory                     %d\n",  // int
                prop.managedMemory );
            printf( "isMultiGpuBoard                   %d\n",  // int
                prop.isMultiGpuBoard );
            printf( "multiGpuBoardGroupID              %d\n",  // int
                prop.multiGpuBoardGroupID );
            printf( "singleToDoublePrecisionPerfRatio  %d\n",  // int
                prop.singleToDoublePrecisionPerfRatio );
            printf( "pageableMemoryAccess              %d\n",  // int
                prop.pageableMemoryAccess );
            printf( "concurrentManagedAccess           %d\n",  // int
                prop.concurrentManagedAccess );
            printf( "computePreemptionSupported        %d\n",  // int
                prop.computePreemptionSupported );
            printf( "canUseHostPointerForRegisteredMem %d\n",  // int
                prop.canUseHostPointerForRegisteredMem );
            printf( "cooperativeLaunch                 %d\n",  // int
                prop.cooperativeLaunch );
        }
    }
    catch (std::exception const& ex) {
        printf( "Error: %s\n", ex.what() );
    }
    return 0;
}
