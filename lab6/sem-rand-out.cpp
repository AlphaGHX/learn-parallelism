#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

struct Arg {
  int tid;
  int val;
};

void *print(void *argv) {
  Arg *arg = (Arg *)argv;

  while (1) {
    printf("thread%d: %d\n", arg->tid, arg->val);
    sleep(1);
    arg->val++;
  }
  return 0;
}

int main() {
  pthread_t tid0, tid1;
  Arg arg0 = {0, 0}, arg1 = {1, 0};

  pthread_create(&tid0, NULL, print, &arg0);
  pthread_create(&tid1, NULL, print, &arg1);

  pthread_join(tid0, NULL);
  pthread_join(tid1, NULL);

  return 0;
}
