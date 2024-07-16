#include <shmem.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int provided;

    // Initialize OpenSHMEM with threading support
    shmem_init_thread(SHMEM_THREAD_MULTIPLE, &provided);

    if (provided != SHMEM_THREAD_MULTIPLE) {
        printf("The requested level of thread support is not available\n");
        shmem_finalize();
        return 1;
    }

    // Get the number of PEs (Processing Elements)
    int num_pes = shmem_n_pes();
    // Get my PE number
    int my_pe = shmem_my_pe();

    printf("Hello from PE %d out of %d PEs\n", my_pe, num_pes);

    // Finalize OpenSHMEM
    shmem_finalize();
    return 0;
}
