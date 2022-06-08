#include <omp.h>
#include <sys/time.h>

#include <cstdlib>
#include <iostream>

#define ll long long

using namespace std;

double sum;
ll num;

void run() {
  int t = omp_get_thread_num();
  int at = omp_get_num_threads();
  ll part = num / at;
  double ans = 0;
  int left = t == 0 ? 1 : t * part;
  int right = t == at - 1 ? num : (t + 1) * part - 1;
  
  ll x = 1;
  short flag = left & 1 ? 1 : -1;  // 通过起始位置判断奇偶
  x += (left - 1) << 1;            // 通过起始位置计算除数

  for (ll i = left; i <= right; ++i) {
    ans += double(flag) / double(x);
    flag = -flag;
    x += 2;
  }

  #pragma omp critical
  sum += ans;
  
  return;
}

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  num = atoll(argv[2]);
  timeval t1, t2;
  double timeuse;

  gettimeofday(&t1, NULL);  // 并行计算开始

  #pragma omp parallel num_threads(threads)
  run();

  gettimeofday(&t2, NULL);  // 并行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("Pi   = %.15f \nTime = %fms\n", sum * 4, timeuse * 1000.0);

  return 0;
}

// pi: 3.1415926535897932384626433832795028841971693993
