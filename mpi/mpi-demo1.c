#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int myid, np;

    MPI_Init(&argc, &argv); // 初始化MPI环境
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // 获取当前进程的排名
    MPI_Comm_size(MPI_COMM_WORLD, &np); // 获取总进程数

    printf("Hello from process %d of %d\n", myid, np);

    MPI_Finalize(); // 结束MPI环境
    return 0;
}
