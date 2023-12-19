#include <stdio.h>


__global__ void printHelloCuda_1()
{
    // printf("gridDim[%d, %d, %d]\n", gridDim.x, gridDim.y, gridDim.z);
    printf("blockIdx[%d, %d, %d]\n", blockIdx.x, blockIdx.y, blockIdx.z);

    // printf("blockDim[%d, %d, %d]\n", blockDim.x, blockDim.y, blockDim.z);
    printf("threadIdx[%d, %d, %d]\n", threadIdx.x, threadIdx.y, threadIdx.z);


    int globalIndexX = blockIdx.x * blockDim.x + threadIdx.x;
    int globalIndexY = blockIdx.y * blockDim.y + threadIdx.y;
    int globalIndexZ = blockIdx.z * blockDim.z + threadIdx.z;

    printf("globalIndex[%d, %d, %d]\n", globalIndexX, globalIndexY, globalIndexZ);

    int globalIndex = globalIndexZ * gridDim.y * gridDim.x * blockDim.z * blockDim.y * blockDim.x +
                      globalIndexY * gridDim.x * blockDim.y * blockDim.x +
                      globalIndexX * blockDim.x;
    
    printf("globalIndex[%d]\n", globalIndex);
}

__global__ void printHelloCuda_2()
{
    int globalIndexX = blockIdx.x * blockDim.x + threadIdx.x;
    int globalIndexY = blockIdx.y * blockDim.y + threadIdx.y;
    int globalIndexZ = blockIdx.z * blockDim.z + threadIdx.z;


    // 这个 globalIndex 为什么要除以2 才是想要全局索引？？？
    int globalIndex = globalIndexZ * gridDim.y * gridDim.x * blockDim.z * blockDim.y * blockDim.x +
                      globalIndexY * gridDim.x * blockDim.y * blockDim.x +
                      globalIndexX * blockDim.x;
    

    printf("<<<grids, block>>> Info : {gridDim[%d, %d, %d], blockDim[%d, %d, %d]}\n", gridDim.x, gridDim.y, gridDim.z, blockDim.x, blockDim.y, blockDim.z);
    
    printf("I am globalIndex[%d], globalIndex[%d, %d, %d], in blockIdx[%d, %d, %d], in threadIdx[%d, %d, %d]\n", 
            globalIndex / 2, globalIndexX, globalIndexY, globalIndexZ, 
            blockIdx.x, blockIdx.y, blockIdx.z,
            threadIdx.x, threadIdx.y, threadIdx.z);
}


__global__ void printHelloCuda_3()
{
    int globalIndexX = blockIdx.x * blockDim.x + threadIdx.x;
    int globalIndexY = blockIdx.y * blockDim.y + threadIdx.y;
    int globalIndexZ = blockIdx.z * blockDim.z + threadIdx.z;


    // 求全局索引公式: 全局索引 = blockNum * blockSize + threadNum(in block)

    // 将block索引坐标 （blockIdx.x, blockIdx.y, blockIdx.z) 转成 一维block索引
    int blockNum  = blockIdx.z * (gridDim.x * gridDim.y) + blockIdx.y * (gridDim.x) + blockIdx.x;

    // 通过block的维度，求一个block有多少个线程
    int blockSize = blockDim.x * blockDim.y * blockDim.z;

    // 将thread索引坐标 [threadIdx.x, threadIdx.y, threadIdx.z] 转成 一维thread索引
    int threadNum = threadIdx.z * (blockDim.x * blockDim.y) + threadIdx.y * (blockDim.x) + threadIdx.x;

    // 求全局索引公式: 全局索引 = blockNum * blockSize + threadNum(in block) // {我这个线程是在第几个block * blocksize + 我这个线程在这个block的索引}
    int globalIndex = blockNum * blockSize + threadNum;
    

    printf("<<<grids, block>>> Info : {gridDim[%d, %d, %d], blockDim[%d, %d, %d]}\n", gridDim.x, gridDim.y, gridDim.z, blockDim.x, blockDim.y, blockDim.z);
    
    printf("I am globalIndex[%d], globalIndex[%d, %d, %d], in blockIdx[%d, %d, %d], in threadIdx[%d, %d, %d]\n", 
            globalIndex, globalIndexX, globalIndexY, globalIndexZ, 
            blockIdx.x, blockIdx.y, blockIdx.z,
            threadIdx.x, threadIdx.y, threadIdx.z);
}

__global__ void printHelloCuda_4()
{
    int globalIndexX = blockIdx.x * blockDim.x + threadIdx.x;
    int globalIndexY = blockIdx.y * blockDim.y + threadIdx.y;
    int globalIndexZ = blockIdx.z * blockDim.z + threadIdx.z;

    int globalDimX = gridDim.x * blockDim.x;
    int globalDimY = gridDim.y * blockDim.y;
    int globalDimZ = gridDim.z * blockDim.z;


    // 求全局索引原理：把grid和blocks看作是一个大的cube
    // thread的坐标是[globalIndexX, globalIndexY, globalIndexZ]
    // 这个大的cube的维度是[globalDimX, globalDimY, globalDimZ]

    int globalIndex = globalIndexZ * (globalDimY * globalDimX) + globalIndexY * (globalDimX) + globalIndexX;
    

    printf("in printHelloCuda_4, <<<grids, block>>> Info : {gridDim[%d, %d, %d], blockDim[%d, %d, %d]}\n", gridDim.x, gridDim.y, gridDim.z, blockDim.x, blockDim.y, blockDim.z);
    
    printf("I am globalIndex[%d], globalIndex[%d, %d, %d], in blockIdx[%d, %d, %d], in threadIdx[%d, %d, %d]\n", 
            globalIndex, globalIndexX, globalIndexY, globalIndexZ, 
            blockIdx.x, blockIdx.y, blockIdx.z,
            threadIdx.x, threadIdx.y, threadIdx.z);
}


int main() {


    // printHelloCuda_3<<<3, 1>>>();
    // printHelloCuda_3<<<1, 3>>>();

    dim3 grids(2,2,1);
    dim3 blocks(2,1,1);
    // printHelloCuda_1<<<grids, blocks>>>();
    // printHelloCuda_2<<<grids, blocks>>>();
    // printHelloCuda_3<<<grids, blocks>>>();
    printHelloCuda_4<<<grids, blocks>>>();


     // 检查核函数执行是否失败
    cudaError_t cudaStatus = cudaGetLastError();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "Kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
        return 1;
    }

    cudaDeviceSynchronize();

    return 0;
}

// blockIdx     与 gridDim  相对应
// threadIdx    与 blockDim 相对应

// <<<grids, block>>> Info : {gridDim[2, 1, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 1, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 1, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 1, 1], blockDim[2, 1, 1]}
// I am globalIndex[0], globalIndex[0, 0, 0], in blockIdx[0, 0, 0], in threadIdx[0, 0, 0]
// I am globalIndex[1], globalIndex[1, 0, 0], in blockIdx[0, 0, 0], in threadIdx[1, 0, 0]
// I am globalIndex[2], globalIndex[2, 0, 0], in blockIdx[1, 0, 0], in threadIdx[0, 0, 0]
// I am globalIndex[3], globalIndex[3, 0, 0], in blockIdx[1, 0, 0], in threadIdx[1, 0, 0]




// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// <<<grids, block>>> Info : {gridDim[2, 2, 1], blockDim[2, 1, 1]}
// I am globalIndex[4], globalIndex[2, 1, 0], in blockIdx[1, 1, 0], in threadIdx[0, 0, 0]
// I am globalIndex[5], globalIndex[3, 1, 0], in blockIdx[1, 1, 0], in threadIdx[1, 0, 0]
// I am globalIndex[0], globalIndex[0, 0, 0], in blockIdx[0, 0, 0], in threadIdx[0, 0, 0]
// I am globalIndex[1], globalIndex[1, 0, 0], in blockIdx[0, 0, 0], in threadIdx[1, 0, 0]
// I am globalIndex[2], globalIndex[0, 1, 0], in blockIdx[0, 1, 0], in threadIdx[0, 0, 0]
// I am globalIndex[3], globalIndex[1, 1, 0], in blockIdx[0, 1, 0], in threadIdx[1, 0, 0]
// I am globalIndex[2], globalIndex[2, 0, 0], in blockIdx[1, 0, 0], in threadIdx[0, 0, 0]
// I am globalIndex[3], globalIndex[3, 0, 0], in blockIdx[1, 0, 0], in threadIdx[1, 0, 0]