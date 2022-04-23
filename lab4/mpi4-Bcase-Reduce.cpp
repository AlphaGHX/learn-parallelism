#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "msmpi.lib")

int main() {
  int comm_sz, my_rank;
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int n = 8;

  int *x = (int *)malloc(sizeof(int) * n);
  int *y = (int *)malloc(sizeof(int) * n);
  int *z = (int *)malloc(sizeof(int) * n);

  memset(z, 0, sizeof(*z));

  for (int i = 0; i < n; ++i) {
    z[i] = 0;
  }

  if (my_rank == 0) {
    for (int i = 0; i < n; ++i) {
      scanf(" %d", &x[i]);
    }
    for (int i = 0; i < n; ++i) {
      scanf(" %d", &y[i]);
    }
  }

  MPI_Bcast(x, n, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(y, n, MPI_INT, 0, MPI_COMM_WORLD);

  for (int i = my_rank * 2; i < my_rank * 2 + 2; ++i) {
    z[i] = x[i] + y[i];
  }

  int *ans = (int *)malloc(sizeof(int) * n);

  MPI_Reduce(z, ans, n, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (my_rank == 0) {
    for (int i = 0; i < n; ++i) {
      printf("%d\n", ans[i]);
    }
  }

  MPI_Finalize();
  return 0;
}

/*
in:
1 2 3 4 5 6 7 8
0 1 2 3 4 5 6 7
out:
1
3
5
7
9
11
13
15
*/
