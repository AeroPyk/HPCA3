#include <stdio.h>
#include <omp.h>
#include <mpi.h>


int main(int argc, char *argv[]) {

    int rank, size, provided;

    float A[10];

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided); // Forking

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (rank == 0) {
        for (int i = 0; i < 5; ++i) {
            A[i] = i;
        }
        printf("(%d/%d)>>>Sending out A", rank, size);
        for (int j = 1; j < size; ++j) {
            MPI_Send(A, 5, MPI_FLOAT, j, 0, MPI_COMM_WORLD);
        }

    } else {

        MPI_Recv(A, 10, MPI_FLOAT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("(%d/%d)>>>Here are my values for A: ", rank, size);

        for (int j = 0; j < 5; ++j) {
            printf("%f ", A[j]);
        }
        printf("\n");

    }


    MPI_Finalize();

    return 0;
}
