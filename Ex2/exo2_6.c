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

    
    if(rank == 0){
        MPI_Win win;
        double* results;
        MPI_Win_allocate(size*sizeof(double), sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &results, &win); //allocate memory and expose it in RMA

        MPI_Win_fence(0, win);
        MPI_Win_fence(0, win);

        double global_result=0;
        results[0] = pi;
        int i;
        for(i=0;i<size;i++){
            global_result+=results[i];
        }

        MPI_Win_free(&win);

        printf("The result is %f\n", global_result);
        printf("Time = %f\n", MPI_Wtime() - time);  

    } else {
        MPI_Win win;
        double expose;
        MPI_Win_create(&expose, sizeof(double), sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &win); //expose pi to RMA
        expose = pi;

        MPI_Win_fence(0, win);
        MPI_Put(&expose, 1, MPI_DOUBLE, 0, rank, size, MPI_DOUBLE, win); //put pi in 0's RMA
        MPI_Win_fence(0, win);

        MPI_Win_free(&win); //close window
    }

    MPI_Finalize();
    return 0;
}

