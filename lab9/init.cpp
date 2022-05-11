#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>

struct Buffer {
  int queue[5];
  int front;
  int rear;
};

int main() {
  int shm_fd = shm_open("buffer", O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, 4096);
  Buffer *buffer = (Buffer *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

  memset(buffer->queue, -1, sizeof buffer->queue);
  buffer->front = buffer->rear = 0;

  sem_open("mutex", O_CREAT, 0666, 1);
  sem_open("empty", O_CREAT, 0666, 5);
  sem_open("full", O_CREAT, 0666, 0);
  return 0;
}
