#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int thread_count = 3;
int count;

sem_t count_sem, barrier_sem;

struct Run {
  int tid;
  int delay;
};

void *run(void *arg) {
  Run *info = (Run *)arg;

  sem_wait(&count_sem);
  sleep(info->delay);
  printf("Thread %d reached the barrier.\n", info->tid);
  if (count == thread_count - 1)
    for (int i = 0; i < thread_count; ++i) sem_post(&barrier_sem);
  count++;
  sem_post(&count_sem);
  sem_wait(&barrier_sem);
  printf("Thread %d passed the barrier.\n", info->tid);

  return 0;
}

int main() {
  Run info[thread_count];
  pthread_t tid[thread_count];

  sem_init(&count_sem, 0, 1);
  sem_init(&barrier_sem, 0, 0);

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
