#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
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

  int *recvx = (int *)malloc(sizeof(int) * 2);
  int *recvy = (int *)malloc(sizeof(int) * 2);

  if (my_rank == 0) {
    for (int i = 0; i < n; ++i) {
      scanf(" %d", &x[i]);
    }
    for (int i = 0; i < n; ++i) {
      scanf(" %d", &y[i]);
    }
  }

  MPI_Scatter(x, 2, MPI_INT, recvx, 2, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(y, 2, MPI_INT, recvy, 2, MPI_INT, 0, MPI_COMM_WORLD);

  int *partAdd = (int *)malloc(sizeof(int) * 2);

  for (int i = 0; i < 2; ++i) {
    partAdd[i] = recvx[i] + recvy[i];
  }

  MPI_Gather(partAdd, 2, MPI_INT, z, 2, MPI_INT, 0, MPI_COMM_WORLD);

  if (my_rank == 0) {
    for (int i = 0; i < n; ++i) {
      printf("%d\n", z[i]);
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
