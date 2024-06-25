/*
 * say hello world from each openmp thread
 * dont forget to compile with -fopenmp
 * remember, this is C, so counting starts at zero
 * so 8 threads are numbered 0 to 7.
 */

#include <omp.h>
#include <stdio.h>

int main() {
  #pragma omp parallel
  {
    int threadID = omp_get_thread_num();
    int threads = omp_get_num_threads();
    printf("hello world from thread %d of %d\n", threadID, threads);
  }
}
