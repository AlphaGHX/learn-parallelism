#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "msmpi.lib")

int main(int argc, char **argv) {
  int comm_sz, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  if (my_rank == 0) {
    int ans = 0, rec;
    int num = atoi(argv[1]);
    int part = num / comm_sz;
    for (int i = 0; i < comm_sz - 1; ++i) {
      int trx[] = {i * part + 1, (i + 1) * part};  // 给定其他三个进程的计算范围
      MPI_Send(trx, 2, MPI_INT, i + 1, 0,
               MPI_COMM_WORLD);  // 向第i号进程发送计算范围
      MPI_Recv(&rec, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      ans += rec;
    }
    printf("进程%d计算范围: %d, %d\n", my_rank, 3 * part + 1, num);
    for (int i = (comm_sz - 1) * part + 1; i <= num; ++i)  // 自己的计算范围
    {
      ans += i;
    }
    printf("进程%d得到结果：%d\n", my_rank, ans);
  } else {
    int trx[2], ans = 0;
    MPI_Recv(trx, 2, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);  // 其他进程接受计算范围
    printf("进程%d计算范围: %d, %d\n", my_rank, trx[0], trx[1]);
    for (int i = trx[0]; i <= trx[1]; ++i) {
      ans += i;
    }
    MPI_Send(&ans, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}