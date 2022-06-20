// 发送函数 MPI_Send 与接收函数 MPI_Recv。
// 请开4个进程运行

#include <mpi.h>
#include <stdio.h>

int main() {
  int comm_sz, my_rank;
  char msg[20];
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0) {
    // 发送
    MPI_Send("hello", 5 + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    MPI_Send("hello", 5 + 1, MPI_CHAR, 2, 0, MPI_COMM_WORLD);
    MPI_Send("hello", 5 + 1, MPI_CHAR, 3, 0, MPI_COMM_WORLD);
  } else {
    // 接收
    MPI_Recv(msg, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("%s\n", msg);
  }

  MPI_Finalize();
  return 0;
}
