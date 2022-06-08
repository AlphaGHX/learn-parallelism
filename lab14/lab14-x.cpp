#include <omp.h>
#include <sys/time.h>

#include <cstdlib>
#include <cstring>
#include <iostream>

#define ll long long

using namespace std;

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  ll num = atoll(argv[2]);
  timeval t1, t2;
  double timeuse;
  double sum;

  gettimeofday(&t1, NULL);  // 并行计算开始
#pragma omp parallel for num_threads(threads) reduction(+ : sum)
  for (ll i = 0; i < num; ++i) {
    if (i % 2 == 0)
      sum += 1.0 / (2 * i + 1);
    else
      sum += -1.0 / (2 * i + 1);
  }
  gettimeofday(&t2, NULL);  // 并行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("并行：\nPi   = %.15f \nTime = %fms\n", sum * 4, timeuse * 1000.0);

  sum = 0;

  gettimeofday(&t1, NULL);  // 串行计算开始
  double factor = 1.0;

  for (ll i = 0; i < num; ++i) {
    sum += factor / (2 * i + 1);
    factor = -factor;
  }
  gettimeofday(&t2, NULL);  // 串行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("串行：\nPi   = %.15f \nTime = %fms\n", sum * 4, timeuse * 1000.0);

  return 0;
}

// pi: 3.1415926535897932384626433832795028841971693993
