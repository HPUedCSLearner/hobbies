#include<string.h>
#include<sys/time.h>
#include<stdio.h>


#define N (8)

__global__ void add_kernal(int *a, int *b, int *c, int size) 
{

    int globalIndexX = blockIdx.x * blockDim.x + threadIdx.x;
    int globalIndexY = blockIdx.y * blockDim.y + threadIdx.y;
    int globalIndexZ = blockIdx.z * blockDim.z + threadIdx.z;

    int globalIndex = globalIndexZ * size * size + globalIndexY * size + globalIndexX;
    c[globalIndex] = a[globalIndex] + b[globalIndex] + 1;

}

int main()
{

    struct timeval start, end;
    double c_time_use;
    double g_time_use;

    int a[N][N][N][N][N][N];
    int b[N][N][N][N][N][N];
    int c[N][N][N][N][N][N];
    int C[N][N][N][N][N][N];

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));

    printf("a has %ld bytes\n", sizeof(a) * 4);
    printf("b has %ld bytes\n", sizeof(b) * 4);
    printf("c has %ld bytes\n", sizeof(c) * 4);



    // cudaMalloc()
    int *d_a, *d_b, *d_c;
    // cudaMallocManaged((void**)&d_a, N*N*N*N*N*N*sizeof(int));
    cudaMalloc((void**)&d_a, N*N*N*N*N*N*sizeof(int));
    cudaMalloc((void**)&d_b, N*N*N*N*N*N*sizeof(int));
    cudaMalloc((void**)&d_c, N*N*N*N*N*N*sizeof(int));

    cudaMemcpy(d_a, a, N*N*N*N*N*N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, N*N*N*N*N*N*sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, N*N*N*N*N*N*sizeof(int), cudaMemcpyHostToDevice);

    // printf("测试主机可否访问，设备内存%d\n", d_a[0][0][0][0][0][0]); // expression must have pointer-to-object type but it has type "int"

    // CPU 运算
    gettimeofday(&start, NULL);

                        for(int n = 0; n < N; ++n) {
                    for(int m = 0; m < N; ++m) {
                for(int l = 0; l < N; ++l) {
            for(int k = 0; k < N; ++k) {
        for(int j = 0; j < N; ++j) {
    for(int i = 0; i < N; ++i) {
                            c[i][j][k][l][m][n] = a[i][j][k][l][m][n] + b[i][j][k][l][m][n] + 1;
                        }
                    }
                }

            }
        }
    }
    gettimeofday(&end, NULL);


    c_time_use = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;

    printf("cpu time ues %lf\n", c_time_use);

    // check
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                for(int l = 0; l < N; ++l) {
                    for(int m = 0; m < N; ++m) {
                        for(int n = 0; n < N; ++n) {
                            if ( c[i][j][k][l][m][n]  != 1) {
                                printf("cal error, expect 1, error at (%d,%d,%d,%d,%d,%d)", i, j, k, l, m, n);
                                break;
                            }
                        }
                    }

                }

            }
        }
    }

    // GPU 运算
    dim3 blocks(N, N, N);
    dim3 grids(N,N,N);

    gettimeofday(&start, NULL);
    add_kernal<<<grids, blocks>>>(d_a, d_b, d_c, N);
    cudaDeviceSynchronize();
    gettimeofday(&end, NULL);

    g_time_use = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;

    printf("gpu time ues %lf\n", g_time_use);

    cudaMemcpy(C, d_c, N*N*N*N*N*N*sizeof(int), cudaMemcpyDeviceToHost);

    // check
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            for(int k = 0; k < N; ++k) {
                for(int l = 0; l < N; ++l) {
                    for(int m = 0; m < N; ++m) {
                        for(int n = 0; n < N; ++n) {
                            if ( C[i][j][k][l][m][n]  != 1) {
                                printf("cal error, expect 1, error at (%d,%d,%d,%d,%d,%d)\n", i, j, k, l, m, n);
                                break;
                            }
                            break;
                        }
                        break;
                    }
                    break;
                }
                break;
            }
            break;
        }
        break;
    }

    printf("speed up: %lf\n", c_time_use / g_time_use);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}