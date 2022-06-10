/* File:     omp_pi.c
 * Purpose:  Estimate pi using OpenMP and the formula
 *
 *              pi = 4*[1 - 1/3 + 1/5 - 1/7 + 1/9 - . . . ]
 *
 * Compile:  gcc -g -Wall -fopenmp -o omp_pi omp_pi.c -lm
 * Run:      omp_pi <thread_count> <n>
 *           thread_count is the number of threads
 *           n is the number of terms of the series to use
 *
 * Input:    none
 * Output:   The estimate of pi and the value of pi computed by the
 *           arctan function in the math library
 *
 * Notes:
 *    1.  The radius of convergence is only 1.  So the series converges
 *        *very* slowly.
 *
 * IPP:   Section 5.5.4 (pp. 229 and ff.)
 */

#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void Usage(char* prog_name);

int main(int argc, char* argv[]) {
  long long n, i;
  int thread_count;
  double factor;
  double sum = 0.0;
  double start, finish;

  if (argc != 3) Usage(argv[0]);
  thread_count = strtol(argv[1], NULL, 10);
  n = strtoll(argv[2], NULL, 10);
  if (thread_count < 1 || n < 1) Usage(argv[0]);

  printf("With n = %lld terms and %d threads,\n", n, thread_count);
  printf("公式计算 pi = %.14f\n", 4.0 * atan(1.0));

  start = omp_get_wtime();
  factor = 1.0;
  for (i = 0; i < n; i++) {
    sum += factor / (2 * i + 1);
    factor = -factor;
  }
  finish = omp_get_wtime();
  printf("串行计算 pi = %.14f\n串行用时 time = %.6fs\n", 4.0 * sum,
         finish - start);

  sum = 0.0;
  start = omp_get_wtime();
#pragma omp parallel num_threads(thread_count) reduction(+ : sum) private(factor)
  {
    if ((omp_get_thread_num() * (n / thread_count)) % 2 == 0)
      factor = 1.0;
    else
      factor = -1.0;
#pragma omp for
    for (i = 0; i < n; i++) {
      sum += factor / (2 * i + 1);
      factor = -factor;
#ifdef DEBUG
      printf("Thread %d > i = %lld, my_sum = %f\n", my_rank, i, my_sum);
#endif
    }
  }
  finish = omp_get_wtime();
  printf("并行计算 pi = %.14f\n并行用时 time = %.6fs\n", 4.0 * sum,
         finish - start);
  return 0;
} /* main */

/*------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message explaining how to run the program
 * In arg:    prog_name
 */
void Usage(char* prog_name) {
  fprintf(stderr, "usage: %s <thread_count> <n>\n", prog_name); /* Change */
  fprintf(stderr,
          "   thread_count is the number of threads >= 1\n"); /* Change */
  fprintf(stderr, "   n is the number of terms and should be >= 1\n");
  exit(0);
} /* Usage */
