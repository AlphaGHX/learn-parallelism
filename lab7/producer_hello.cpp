#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

struct DataType {
  int a;
  int b;
};

int main() {
  int shm_fd;
  DataType *ptr;
  shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, 4096);
  ptr = (DataType *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  ptr->a = 123;
  ptr->b = 456;
  return 0;
}
