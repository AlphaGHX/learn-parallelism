#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>

sem_t *empty, *full, *mutex;

struct Buffer {
  int queue[5];
  int front;
  int rear;
};

void *producer(void *arg) {
  int shm_fd = shm_open("buffer", O_RDWR, 0666);
  Buffer *buffer = (Buffer *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  empty = sem_open("empty", O_RDONLY);
  full = sem_open("full", O_RDONLY);
  mutex = sem_open("mutex", O_RDONLY);

  while (1) {
    sem_wait(empty);
    sem_wait(mutex);

    srand((unsigned)time(NULL));
    sleep((rand() % 4) + 1);
    buffer->queue[buffer->rear++ % 5] = rand();
    std::cout << "p: " << buffer->queue[(buffer->rear - 1) % 5] << std::endl;

    sem_post(mutex);
    sem_post(full);
  }
}

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  int time = atoi(argv[2]);

  pthread_t tid;

  while (threads--) pthread_create(&tid, NULL, producer, NULL);

  sleep(time);

  return 0;
}
