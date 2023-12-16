#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "This program requires at least two processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        int data = 42;
        int destination = 1;
        int tag = 0;

        MPI_Send(&data, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("Process 0 sent message to process 1.\n");
    } else if (rank == 1) {
        int source = 0;
        int tag = 0;
        MPI_Status status;

        int received_data;
        MPI_Recv(&received_data, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("Process 1 received message from process 0. Data: %d\n", received_data);
    }

    MPI_Finalize();
    return 0;
}
