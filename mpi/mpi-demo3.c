#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int myid, np, left, right;
    int message_out = 42, message_in;

    MPI_Init(&argc, &argv); // 初始化MPI环境
    MPI_Comm_rank(MPI_COMM_WORLD, &myid); // 获取当前进程的排名
    MPI_Comm_size(MPI_COMM_WORLD, &np); // 获取总进程数

    // 计算左右相邻进程的排名
    left = (myid - 1 + np) % np;
    right = (myid + 1) % np;

    // 向右相邻进程发送消息
    MPI_Send(&message_out, 1, MPI_INT, right, 0, MPI_COMM_WORLD);

    // 从左相邻进程接收消息
    MPI_Recv(&message_in, 1, MPI_INT, left, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    printf("Process %d received message %d from process %d\n", myid, message_in, left);

    MPI_Finalize(); // 结束MPI环境
    return 0;
}


// feng@feng-X99M-D3:~/test/mpi-test$ mpirun -n 6 ./a.out 
// Process 0 received message 42 from process 5
// Process 1 received message 42 from process 0
// Process 2 received message 42 from process 1
// Process 3 received message 42 from process 2
// Process 4 received message 42 from process 3
// Process 5 received message 42 from process 4
