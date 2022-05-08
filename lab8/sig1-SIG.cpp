#include <unistd.h>

#include <iostream>

using namespace std;

int main() {
  int i = 1;
  while (1) {
    cout << i++ << "Hello World." << endl;
    sleep(1);
  }
}
