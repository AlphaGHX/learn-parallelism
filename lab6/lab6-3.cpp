#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#include <cstdlib>
#include <ctime>
#include <iostream>

sem_t empty, full, mutex;
int queue[5], front = 0, rear = 0;

void *producer(void *arg) {
  while (1) {
    sem_wait(&empty);
    sem_wait(&mutex);

    srand((unsigned)time(NULL));
    sleep(rand() % 5);
    queue[rear++ % 5] = rand();
    std::cout << "p: " << queue[(rear - 1) % 5] << std::endl;

    sem_post(&mutex);
    sem_post(&full);
  }
}

void *consumer(void *arg) {
  while (1) {
    sem_wait(&full);
    sem_wait(&mutex);

    srand((unsigned)time(NULL));
    sleep(rand() % 5);
    std::cout << "c: " << queue[front++ % 5] << std::endl;

    sem_post(&mutex);
    sem_post(&empty);
  }
}

int main(int argc, char *argv[]) {
  int time = atoi(argv[1]);
  int producer_thread = atoi(argv[2]);
  int consumer_thread = atoi(argv[3]);

  pthread_t thrd_prod, thrd_cons;

  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, 5);
  sem_init(&full, 0, 0);

  while (producer_thread--) pthread_create(&thrd_prod, NULL, producer, NULL);
  while (consumer_thread--) pthread_create(&thrd_cons, NULL, consumer, NULL);

  sleep(time);

  std::cout << std::endl << "queue: ";
  for (auto v : queue) std::cout << v << ' ';
  std::cout << std::endl;

  sem_destroy(&mutex);
  sem_destroy(&full);
  sem_destroy(&empty);
  return 0;
}
