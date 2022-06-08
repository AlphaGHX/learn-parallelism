#include <pthread.h>
#include <sys/time.h>

#include <cstdlib>
#include <iostream>

#define ll long long

using namespace std;

pthread_mutex_t mutex;
ll sum;

struct Part {
  ll left;
  ll right;
};

void *add(void *argv) {
  Part *part = (Part *)argv;
  ll ans = 0;

  for (ll i = part->left; i <= part->right; ++i) {
    ans += i;
  }

  pthread_mutex_lock(&mutex);  // 合并时需要互斥累加sum
  sum += ans;
  pthread_mutex_unlock(&mutex);

  return 0;
}

int main(int argc, char **argv) {
  double timeuse;
  int threads = atoi(argv[1]);
  ll num = atoll(argv[2]);
  ll part = num / threads;
  timeval t1, t2;
  pthread_t tid[threads];
  Part parts[threads];

  pthread_mutex_init(&mutex, NULL);

  for (int i = 0; i < threads; ++i) {  // 分配各线程计算范围
    parts[i].left = i == 0 ? 1 : i * part;
    parts[i].right = i == threads - 1 ? num : (i + 1) * part - 1;
  }

  gettimeofday(&t1, NULL);  // Pthread计算开始
  for (int i = 0; i < threads; i++) {
    pthread_create(&tid[i], NULL, add, &parts[i]);
  }
  for (int i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }
  gettimeofday(&t2, NULL);  // Pthread计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("Pthread:\nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  sum = 0;

  gettimeofday(&t1, NULL);  // OpenMP计算开始
#pragma omp parallel for num_threads(threads) reduction(+ : sum)
  for (int i = 1; i <= num; ++i) sum += i;
  gettimeofday(&t2, NULL);  // OpenMP计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("OpenMP:\nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  sum = 0;

  gettimeofday(&t1, NULL);  // 串行计算开始
  for (int i = 1; i <= num; ++i) {
    sum += i;
  }
  gettimeofday(&t2, NULL);  // 串行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("串行: \nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  pthread_mutex_destroy(&mutex);

  return 0;
}
