#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include <cstdlib>
#include <iostream>

#define ll long long

sem_t sem;
double sum;

struct Part {
  ll left;
  ll right;
};

void *add(void *argv) {
  Part *part = (Part *)argv;

  double ans = 0;
  ll x = 1;
  short flag = part->left & 1 ? 1 : -1;  // 通过起始位置判断奇偶
  x += (part->left - 1) << 1;            // 通过起始位置计算除数

  for (ll i = part->left; i <= part->right; ++i) {
    ans += double(flag) / double(x);
    flag = -flag;
    x += 2;
  }

  sem_wait(&sem);  // 等待sem值大于0，如果为0则阻塞
  sum += ans;
  sem_post(&sem);  // sem值加1

  return 0;
}

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  ll num = atoll(argv[2]);

  timeval t1, t2;
  double timeuse;

  pthread_t *tid = (pthread_t *)malloc(threads * sizeof(pthread_t));
  Part *parts = (Part *)malloc(threads * sizeof(Part));
  sem_init(&sem, 0, 0);  // 初始化信号量sem，设置为局部信号量，初始值为0
  ll part = num / threads;

  for (int i = 0; i < threads; ++i) {
    parts[i].left = i == 0 ? 1 : i * part;
    parts[i].right = i == threads - 1 ? num : (i + 1) * part - 1;
  }

  sem_post(&sem);
  gettimeofday(&t1, NULL);  // 并行计算开始

  for (int i = 0; i < threads; i++) {
    pthread_create(&tid[i], NULL, add, &parts[i]);
  }
  for (int i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }

  gettimeofday(&t2, NULL);  // 并行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("并行: \nPi   = %.15f \nTime = %fms\n", sum * 4, timeuse * 1000.0);

  sum = 0;
  short flag = 1;
  ll x = 1;

  gettimeofday(&t1, NULL);  // 串行计算开始

  for (int i = 1; i <= num; ++i) {
    sum += flag * 1.0 / (double)x;
    flag = -flag;
    x += 2;
  }

  gettimeofday(&t2, NULL);  // 串行计算结束

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("串行: \nPi   = %.15f \nTime = %fms\n", sum * 4, timeuse * 1000.0);

  sem_destroy(&sem);

  return 0;
}

// pi: 3.1415926535897932384626433832795028841971693993
