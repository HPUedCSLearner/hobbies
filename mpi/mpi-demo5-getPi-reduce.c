#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define ITERATIONS 1000000000

int main(int argc, char** argv) {
    int rank, size;
    double pi, local_pi;


    double start,end;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start = MPI_Wtime();

    // Each process calculates a part of the sum
    double sum = 0.0;
    for (int i = rank; i < ITERATIONS; i += size) {
        double x = (i + 0.5) / ITERATIONS;
        sum += 4.0 / (1.0 + x * x);
    }

    // Sum up the partial results from all processes
    MPI_Reduce(&sum, &local_pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Process 0 calculates the final result
    if (rank == 0) {
        pi = local_pi / ITERATIONS;
        printf("Approximation of pi: %f\n", pi);
    }

    end=MPI_Wtime();//结束计算时间 
    if(rank==0)
        {
          printf("PI = %.15f\n",pi);
          printf("Time = %lf\n",end-start); 
        }

    MPI_Finalize();
    return 0;
}
