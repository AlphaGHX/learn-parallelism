#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <iostream>

int main() {
  int shm_fd;
  void *ptr;
  shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, 4096);
  ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  sprintf((char *)ptr, "%s", "Hello");

  return 0;
}
