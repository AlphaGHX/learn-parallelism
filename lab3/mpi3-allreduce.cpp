#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib, "msmpi.lib")

int main(int argc, char **argv) {
  int comm_sz, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int num = atoi(argv[1]);   // 获取参数
  int part = num / comm_sz;  // 分割计算任务
  int ans = 0;
  if (my_rank == 0) {
    printf("进程%d计算范围: %d, %d\n", my_rank, (comm_sz - 1) * part + 1, num);
    for (int i = (comm_sz - 1) * part + 1; i <= num; ++i)  // 自己的计算范围
    {
      ans += i;
    }
    int sum;
    MPI_Allreduce(&ans, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("进程%d得到结果：%d\n", my_rank, sum);
  } else {
    printf("进程%d计算范围: %d, %d\n", my_rank, (my_rank - 1) * part + 1,
           my_rank * part);
    for (int i = (my_rank - 1) * part + 1; i <= my_rank * part; ++i) {
      ans += i;
    }
    int sum;
    MPI_Allreduce(&ans, &sum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    printf("进程%d得到结果：%d\n", my_rank, sum);
  }
  MPI_Finalize();
  return 0;
}