#include <stdio.h>
#include <mpi.h>
#pragma comment(lib, "msmpi.lib")

int main()
{
  int comm_sz, my_rank;
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0)
  {
    int fir, sec;
    int ans = 0;
    MPI_Status status;
    for (int i = 0; i < 3; ++i)
    {
      MPI_Recv(&fir, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status); // 接受任意进程的tag为0的信息
      printf("thread%d: %d\n", status.MPI_SOURCE, fir);
      MPI_Recv(&sec, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status); // 接受任意进程的tag为1的信息
      ans += sec;
    }
    printf("ans: %d\n", ans);
  }
  else
  {
    int fir = my_rank, sec = my_rank * 10;
    MPI_Send(&fir, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // 向0号进程发送tag为0的信息
    MPI_Send(&sec, 1, MPI_INT, 0, 1, MPI_COMM_WORLD); // 向0号进程发送tag为1的信息
  }

  MPI_Finalize();
  return 0;
}
