// 示例：散射函数 MPI_Scatter 与聚集函数 MPI_Gather
// 示例程序为向量求和
// mpicc prog4.c -o prog4.out
// mpiexec -oversubscribe -n 5 ./prog4.out

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int comm_sz, my_rank;
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int n = 10;

  int *x = malloc(sizeof(int) * n);
  int *y = malloc(sizeof(int) * n);
  int *z = malloc(sizeof(int) * n);

  int *recvx = malloc(sizeof(int) * 2);
  int *recvy = malloc(sizeof(int) * 2);

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

  int *partAdd = malloc(sizeof(int) * 2);

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
开启 5 个进程
in:
1 2 3 4 5 6 7 8 9 10
0 1 2 3 4 5 6 7 8 9
out:
1
3
5
7
9
11
13
15
17
19
*/
