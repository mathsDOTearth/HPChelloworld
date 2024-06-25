// Hybrid MPI/OpenMP hello world program
#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int provided;

// Tell the program we are going to use hybrid MPI/OpenMP
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided < MPI_THREAD_FUNNELED) {
        fprintf(stderr, "The MPI implementation does not support the required level of threading.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

// Initialise MPI
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

// Ensure that there are exactly 2 MPI processes
    if (world_size != 2) {
        fprintf(stderr, "This application requires exactly 2 MPI processes.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

// 
    double start_time, end_time;
    if (world_rank == 0) {
        start_time = MPI_Wtime();
    }

// For this example, use 4 OpenMP threads per MPI processvi	
    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
// Print out the current thread ID and Process ID
        printf("Hello World from OpenMP thread %d on MPI process %d\n", thread_id, world_rank);
    }

// Dont really need timing code, but its a good habbit to put it in all MPI programs
    if (world_rank == 0) {
        end_time = MPI_Wtime();
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
