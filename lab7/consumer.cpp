#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>

int main() {
  int shm_fd;
  void *ptr;
  shm_fd = shm_open("OS", O_RDONLY, 0666);
  ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);
  printf("%s\n", (char *)ptr);
  shm_unlink("OS");

  return 0;
}
