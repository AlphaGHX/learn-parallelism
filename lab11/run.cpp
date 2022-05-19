#include <pthread.h>
#include <unistd.h>

#include <iostream>

using namespace std;

pthread_mutex_t mutex;
int thread_count = 3;
int count;

struct Run {
  int tid;
  int delay;
};

void *run(void *arg) {
  Run *info = (Run *)arg;

  // 互斥
  sleep(info->delay);
  printf("Thread %d reached the barrier.\n", info->tid);
  pthread_mutex_lock(&mutex);
  count++;
  pthread_mutex_unlock(&mutex);

  // 忙等待
  while (count < thread_count)
    ;

  printf("Thread %d passed the barrier.\n", info->tid);
  return 0;
}

int main() {
  Run info[thread_count];
  pthread_t tid[thread_count];

  pthread_mutex_init(&mutex, NULL);

  for (int i = 1; i <= thread_count; ++i) {
    info[i - 1] = {i, i * 2};
  }

  for (int i = 0; i < thread_count; ++i) {
    pthread_create(&tid[i], NULL, run, &info[i]);
  }

  for (int i = 0; i < thread_count; i++) {
    pthread_join(tid[i], NULL);
  }
}
