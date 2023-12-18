#include <stdio.h>

int main() {
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    for (int i = 0; i < deviceCount; ++i) {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, i);

        printf("Device %d:\n", i);
        printf("  Name: %s\n", deviceProp.name);
        printf("  Max threads per block: %d\n", deviceProp.maxThreadsPerBlock);
        printf("  Max threads per multiprocessor: %d\n", deviceProp.maxThreadsPerMultiProcessor);
        // 可以查询其他属性

        printf("\n");
    }

    return 0;
}


// ==========A 100============
// Device 0:
//   Name: NVIDIA A100 80GB PCIe
//   Max threads per block: 1024
//   Max threads per multiprocessor: 2048