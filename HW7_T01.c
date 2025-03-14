/* include OpenMP API header */
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv){
  omp_set_num_threads(24);
  
#pragma omp parallel
  { /* start parallel region */
    int numThreads = omp_get_num_threads();
    int threadIdeven = omp_get_thread_num() % 2 == 0;
    int threadIdodd = omp_get_thread_num() % 2 == 1;
    if(threadIdodd)
      printf("Hello from Odd thread: %d threads\n", numThreads);
    if(threadIdeven)
      printf("Even thread too: %d threads\n", numThreads);
  } /* end parallel region */
exit(0);
}
