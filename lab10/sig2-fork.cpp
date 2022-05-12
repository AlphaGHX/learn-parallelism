#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

int main() {
  pid_t pid;

  pid = fork();
  
  if (pid == 0) {
    sleep(5);
    exit(0);
  }
  
  std::cout << "父进程等待..." << std::endl;
  wait(NULL);
  std::cout << "父进程结束" << std::endl;
  exit(0);
}
