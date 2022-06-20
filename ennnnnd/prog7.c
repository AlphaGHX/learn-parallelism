// parallel for 指令
// 查看 whaaaaat.md 和 lab13 和 lab14 及 lab15

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  long sum = 0;
  int threads = atoi(argv[1]);
  long n = atol(argv[2]);

#pragma omp parallel for num_threads(threads) reduction(+ : sum)
  for (int i = 1; i <= n; ++i) sum += i;
  printf("%ld\n", sum);

  return 0;
}
