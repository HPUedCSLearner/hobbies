#include <iostream>
#include <cstdlib>
#include <ctime>

// CPU 串行版本的向量加法
void addVectorCPU(int* a, int* b, int* c, int size) {
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }
}

// GPU 版本的向量加法
__global__ void addVectorGPU(int* a, int* b, int* c, int size) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < size) {
        c[tid] = a[tid] + b[tid];
    }
}

int main() {
    const int size = 1000000;
    const int threadsPerBlock = 256;
    const int blocksPerGrid = (size + threadsPerBlock - 1) / threadsPerBlock;

    // 分配和初始化向量
    int* a = new int[size];
    int* b = new int[size];
    int* c_cpu = new int[size];
    int* c_gpu = new int[size];

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // CPU 串行版本的向量加法
    clock_t start_cpu = clock();
    addVectorCPU(a, b, c_cpu, size);
    clock_t end_cpu = clock();
    double cpu_time = static_cast<double>(end_cpu - start_cpu) / CLOCKS_PER_SEC;

    // GPU 版本的向量加法
    int* d_a, *d_b, *d_c;
    cudaMallocManaged((void**)&d_a, size * sizeof(int));
    cudaMallocManaged((void**)&d_b, size * sizeof(int));
    cudaMallocManaged((void**)&d_c, size * sizeof(int));
    //cudaMalloc((void**)&d_a, size * sizeof(int));
    //cudaMalloc((void**)&d_b, size * sizeof(int));
    //cudaMalloc((void**)&d_c, size * sizeof(int));

    cudaMemcpy(d_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size * sizeof(int), cudaMemcpyHostToDevice);

    clock_t start_gpu = clock();
    addVectorGPU<<<blocksPerGrid, threadsPerBlock>>>(d_a, d_b, d_c, size);
    cudaDeviceSynchronize();
    clock_t end_gpu = clock();
    double gpu_time = static_cast<double>(end_gpu - start_gpu) / CLOCKS_PER_SEC;

    cudaMemcpy(c_gpu, d_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    // 检查结果是否一致
    for (int i = 0; i < size; ++i) {
        if (c_cpu[i] != c_gpu[i]) {
            std::cerr << "Error: CPU and GPU results do not match!" << std::endl;
            break;
        }
    }

    // 计算加速比
    double speedup = cpu_time / gpu_time;

    std::cout << "CPU Time: " << cpu_time << " seconds" << std::endl;
    std::cout << "GPU Time: " << gpu_time << " seconds" << std::endl;
    std::cout << "Speedup: " << speedup << "x" << std::endl;

    // 释放内存
    delete[] a;
    delete[] b;
    delete[] c_cpu;
    delete[] c_gpu;

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
