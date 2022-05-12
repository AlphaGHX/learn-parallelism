#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

void sig_fun(int sig) { std::cout << "父进程结束" << std::endl; }

int main() {
  pid_t pid;

  signal(SIGUSR1, sig_fun);

  pid = fork();

  if (pid == 0) {
    sleep(5);
    kill(getppid(), SIGUSR1);
    exit(0);
  }

  std::cout << "父进程等待..." << std::endl;
  pause();
}
