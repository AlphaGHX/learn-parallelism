#include <semaphore.h>

int main() {
  sem_unlink("/sem1");
  sem_unlink("/sem2");
  return 0;
}
