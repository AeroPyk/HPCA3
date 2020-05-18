#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int rank, size, provided;

	MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);

	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	srand(rank);

	printf("Hello World from rank %d from %d process and my rand number is %d\n", rank, size, rand());

	MPI_Finalize();
	return 0;
}