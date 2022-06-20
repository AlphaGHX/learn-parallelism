// 归约函数 MPI_Reduce 使用
// 示例程序为累加程序

#include <mpi.h>

#include <cstdio>
#include <cstdlib>
#define ll long long

int main(int argc, char **argv) {
  int comm_sz, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  ll num = atoll(argv[1]);
  ll part = num / comm_sz;
  ll ans = 0;

  if (my_rank == 0) {
    double startTime, endTime;
    ll sum;
    startTime = MPI_Wtime();
    for (ll i = (comm_sz - 1) * part + 1; i <= num; ++i) {
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
