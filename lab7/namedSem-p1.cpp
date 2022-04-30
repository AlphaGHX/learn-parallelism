#include <semaphore.h>
#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
  int i;
  sem_t *sem1, *sem2;
  sem1 = sem_open("/sem1", 0);
  sem2 = sem_open("/sem2", 0);

  for (i = 1; i <= 10; ++i) {
    sem_wait(sem1);
    cout << "Process1 = " << i << endl;
    sleep(1);
    sem_post(sem2);
  }

  sem_close(sem1);
  sem_close(sem2);

  return 0;
}
