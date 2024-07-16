#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sysconf

void *print_hello_world(void *threadid) {
    long tid;
    tid = (long)threadid;
    printf("Hello, World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    // Get the number of CPU cores
    long num_cores = sysconf(_SC_NPROCESSORS_ONLN);

    // Array to hold thread identifiers
    pthread_t *threads = malloc(num_cores * sizeof(pthread_t));
    if (threads == NULL) {
        printf("ERROR; unable to allocate memory for threads\n");
        exit(-1);
    }

    int rc;
    long t;
    for(t = 0; t < num_cores; t++) {
        printf("In main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, print_hello_world, (void *)t);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for(t = 0; t < num_cores; t++) {
        pthread_join(threads[t], NULL);
    }

    // Free allocated memory
    free(threads);

    // Exit the main thread
    pthread_exit(NULL);
}
