#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ll long long
#pragma comment(lib, "msmpi.lib")

int main(int argc, char **argv) {
  int comm_sz, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  ll num = atoll(argv[1]);  // 获取参数
  ll part = num / comm_sz;  // 分割计算任务
  ll ans = 0;

  if (my_rank == 0) {
    double startTime, endTime;
    ll sum;
    startTime = MPI_Wtime();
    for (ll i = (comm_sz - 1) * part + 1; i <= num; ++i)  // 自己的计算范围
    {
      ans += i;
    }
    MPI_Reduce(&ans, &sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    endTime = MPI_Wtime();
    printf("并行运算结果：\t%lld\n", sum);
    printf("所需时间：\t%0.15f ms\n", (endTime - startTime) * 1000);
  } else {
    for (ll i = (my_rank - 1) * part + 1; i <= my_rank * part; ++i) {
      ans += i;
    }
    MPI_Reduce(&ans, NULL, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
  }
  MPI_Finalize();
  return 0;
}
