#include <signal.h>
#include <unistd.h>

#include <iostream>

int timeX;

void sig_fun(int sig) { std::cout << "过去" << timeX << "秒." << std::endl; }

int main(int argc, char **argv) {
  timeX = atoi(argv[1]);

  alarm(timeX);
  signal(SIGALRM, sig_fun);

  pause();

  return 0;
}
