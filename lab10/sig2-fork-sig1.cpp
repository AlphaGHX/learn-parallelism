#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>

void sig_fun(int sig) { std::cout << "父进程结束" << std::endl; }

int main() {
  pid_t pid;

  signal(SIGALRM, sig_fun);

  pid = fork();

  if (pid == 0) {
    sleep(5);
    kill(getppid(), SIGALRM);
    exit(0);
  }

  std::cout << "父进程等待..." << std::endl;
  pause();
}
