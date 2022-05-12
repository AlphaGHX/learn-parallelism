#include <unistd.h>

#include <iostream>

int main() {
  pid_t pid;

  pid = fork();
  pid = fork();

  std::cout << pid << std::endl;

  return 0;
}
