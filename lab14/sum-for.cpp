#include <cstdlib>
#include <iostream>

using namespace std;

long sum = 0;

int main(int argc, char **argv) {
  long n = atol(argv[1]);

#pragma omp parallel for num_threads(2)
  for (int i = 1; i <= n; ++i) sum += i;
  cout << "sum=" << sum << endl;

  return 0;
}
