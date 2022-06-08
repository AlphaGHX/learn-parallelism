#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  long sum = 0;
  long n = atol(argv[1]);

#pragma omp parallel for num_threads(2) reduction(+ : sum)
  for (int i = 1; i <= n; ++i) sum += i;

  cout << "sum=" << sum << endl;

  return 0;
}
