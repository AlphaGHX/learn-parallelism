// 发送与接收函数、tag 及命令行参数
// mpicc prog2.c -o prog2.out
// mpiexec -oversubscribe -n 4 ./prog2.out test

#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int comm_sz, my_rank;
  // 得到命令行参数
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0) {
    int fir, sec;
    int ans = 0;
    MPI_Status status;
    for (int i = 0; i < 3; ++i) {
      // 接受任意进程的tag为0的信息
      MPI_Recv(&fir, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
      printf("thread%d: %d\n", status.MPI_SOURCE, fir);
      // 接受任意进程的tag为1的信息
      MPI_Recv(&sec, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      ans += sec;
    }
    printf("ans: %d\n", ans);
    printf("接收到的命令行参数: %s\n", argv[1]);
  } else {
    int fir = my_rank, sec = my_rank * 10;
    // 向0号进程发送tag为0的信息
    MPI_Send(&fir, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    // 向0号进程发送tag为1的信息
    MPI_Send(&sec, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
