#include <signal.h>
#include <unistd.h>

#include <iostream>

using namespace std;

void fun(int sig) {
  cout << "捕获信号: " << sig << endl;
  signal(SIGTSTP, SIG_DFL);
}

int main() {
  int i = 1;
  signal(SIGTSTP, fun);
  while (1) {
    cout << i++ << "Hello World." << endl;
    sleep(1);
  }
}
