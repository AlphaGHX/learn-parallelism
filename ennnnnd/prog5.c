// pthread_create 与互斥、信号量
// 示例程序为累加程序
// gcc prog5.c -o prog5.out
// ./prog5.out 2 1000

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define ll long long

// 互斥量
pthread_mutex_t mutex;
// 信号量
sem_t sem;
ll sum;

typedef struct {
  ll left;
  ll right;
} Part;

// 互斥量实现
void *add_mutex(void *argv) {
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

// 信号量实现
void *add_sem(void *argv) {
  Part *part = (Part *)argv;
  ll ans = 0;

  for (ll i = part->left; i <= part->right; ++i) {
    ans += i;
  }

  sem_wait(&sem);  // 等待sem值大于0，如果为0则阻塞
  sum += ans;
  sem_post(&sem);  // sem值加1

  return 0;
}

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  ll num = atoll(argv[2]);
  ll part = num / threads;
  double timeuse;
  struct timeval t1, t2;
  pthread_t *tid = (pthread_t *)malloc(threads * sizeof(pthread_t));
  Part *parts = (Part *)malloc(threads * sizeof(Part));
  pthread_mutex_init(&mutex, NULL);  // 初始化互斥锁
  sem_init(&sem, 0, 0);  // 初始化信号量sem，设置为局部信号量，初始值为0

  for (int i = 0; i < threads; ++i) {  // 分配各线程计算范围
    parts[i].left = i == 0 ? 1 : i * part;
    parts[i].right = i == threads - 1 ? num : (i + 1) * part - 1;
  }

  gettimeofday(&t1, NULL);  // mutex并行计算开始
  for (int i = 0; i < threads; i++) {
    pthread_create(&tid[i], NULL, add_mutex, &parts[i]);
  }
  for (int i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }
  gettimeofday(&t2, NULL);  // mutex并行计算结束
  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;
  printf("mutex并行: \nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  sum = 0;
  gettimeofday(&t1, NULL);  // sem并行计算开始
  for (int i = 0; i < threads; i++) {
    pthread_create(&tid[i], NULL, add_sem, &parts[i]);
  }
  for (int i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }
  gettimeofday(&t2, NULL);  // sem并行计算结束
  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;
  printf("sem并行: \nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  sum = 0;
  gettimeofday(&t1, NULL);  // 串行计算开始
  for (int i = 1; i <= num; ++i) {
    sum += i;
  }
  gettimeofday(&t2, NULL);  // 串行计算结束
  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;
  printf("串行: \nSum  = %lld \nTime = %fms", sum, timeuse * 1000.0);

  pthread_mutex_destroy(&mutex);
  sem_destroy(&sem);

  return 0;
}
