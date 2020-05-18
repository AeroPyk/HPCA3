#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h>

#define SEED     921
#define NUM_ITER 1000000000

int main(int argc, char* argv[])
{
	int rank, size, provided;
    int count = 0;
    double x, y, z, pi;
    double time;
	
	MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0){
		time = MPI_Wtime();
	}

    srand(SEED * rank); // Important: Multiply SEED by "rank" when you introduce MPI!
    
    // Calculate PI following a Monte Carlo method
    for (int iter = (NUM_ITER/size) * rank; iter < (NUM_ITER/size) * (rank + 1); iter++)
    {
        // Generate random (X,Y) points
        x = (double)random() / (double)RAND_MAX;
        y = (double)random() / (double)RAND_MAX;
        z = sqrt((x*x) + (y*y));
        
        // Check if point is in unit circle
        if (z <= 1.0)
        {
            count++;
        }
    }
    
    // Estimate Pi and display the result
    pi = ((double)count / (double)NUM_ITER) * 4.0;
    
    if(rank != 0){
        MPI_Request req;
    	MPI_Isend(&pi, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &req);
        MPI_Wait(&req, MPI_STATUS_IGNORE);
    } else {
    	double* buf;
        MPI_Request* reqs;
        buf = malloc((size-1) * sizeof(double));
        reqs = malloc((size-1) * sizeof(MPI_Request));
    	int i;
    	for(i=1; i<size; i++){ //no need to start from i=0 since the rank 0 has already its result
    		MPI_Irecv(&buf[i-1], 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &reqs[i-1]);
    	}
        MPI_Waitall(size-1, reqs, MPI_STATUS_IGNORE);
        for(i=1; i<size; i++){
            pi += buf[i];
        }
        free(buf);
        free(reqs);

    	printf("The result is %f\n", pi);
    	printf("Time = %f\n", MPI_Wtime() - time);
    }
	MPI_Finalize();
    return 0;
}

