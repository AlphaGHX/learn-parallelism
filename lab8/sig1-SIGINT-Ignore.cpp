#include <signal.h>
#include <unistd.h>

#include <iostream>

using namespace std;

void fun(int sig) {
  cout << "捕获信号: " << sig << endl;
  signal(SIGINT, SIG_DFL);
}

int main() {
  int i = 1;
  while (1) {
    signal(SIGINT, fun);
    cout << i++ << "Hello World." << endl;
    sleep(1);
  }
}
