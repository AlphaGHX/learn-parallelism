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
  shm_fd = shm_open("OS", O_RDONLY, 0666);
  ptr = (DataType *)mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("%d\n", ptr->a);
  shm_unlink("OS");

  return 0;
}
