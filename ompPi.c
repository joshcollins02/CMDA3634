#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "dphilox.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: ompPi N Nthreads\n");
        exit(-1);
    }

    int Nthreads = atoi(argv[2]);
    omp_set_num_threads(Nthreads);

    int N = atoi(argv[1]);
    int count = 0;

    double tic = omp_get_wtime();

#pragma omp parallel reduction(+:count)
    {
        philox_state state;
        philox_init(&state, omp_get_thread_num() + 1);

#pragma omp for
        for (int n=0;n<N;++n) {
	  double x = dphilox(state.key, n);
	  double y = dphilox(state.key, n + 1);

	  if ((x * x + y * y) <= 1) {
                count++;
	  }
        }
    }

    double pi = 4.0 * count / N;
    double toc = omp_get_wtime();

    printf("Estimated Pi: %f\n", pi);
    printf("Time taken: %f seconds\n", toc - tic);

    return 0;
}
