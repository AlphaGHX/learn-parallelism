#include <semaphore.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  shm_unlink("buffer");

  sem_unlink("mutex");
  sem_unlink("empty");
  sem_unlink("full");

  return 0;
}
