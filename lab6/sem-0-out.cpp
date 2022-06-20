#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

sem_t sem0, sem1;

short first = 0; // 选择需要先输出的进程

struct Arg {
  int tid;
  int val;
};

void *print(void *argv) {
  Arg *arg = (Arg *)argv;

  while (1) {
    arg->tid == first ? sem_wait(&sem0) : sem_wait(&sem1);
    printf("thread%d: %d\n", arg->tid, arg->val);
    arg->tid == first ? sem_post(&sem1) : sem_post(&sem0);
    sleep(1);
    arg->val++;
  }
  return 0;
}

int main() {
  pthread_t tid0, tid1;
  Arg arg0 = {0, 0}, arg1 = {1, 0};

  sem_init(&sem0, 0, 1);
  sem_init(&sem1, 0, 0);

  pthread_create(&tid0, NULL, print, &arg0);
  pthread_create(&tid1, NULL, print, &arg1);

  pthread_join(tid0, NULL);
  pthread_join(tid1, NULL);

  return 0;
}
