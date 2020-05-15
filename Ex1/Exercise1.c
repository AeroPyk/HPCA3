#include <stdio.h>
#include <omp.h>
#include <mpi.h>


int main(int argc, char *argv[]) {

    int rank, size, provided;

    float A[10];

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided); // Forking

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    printf("Hello world from rank %d from %d processes!", rank, size);


    MPI_Finalize();

    return 0;
}
