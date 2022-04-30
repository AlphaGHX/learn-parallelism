#include <fcntl.h>
#include <semaphore.h>

int main() {
  sem_open("/sem1", O_CREAT, 0666, 1);
  sem_open("/sem2", O_CREAT, 0666, 0);

  return 0;
}
