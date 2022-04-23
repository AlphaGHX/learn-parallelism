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
    int rec;
    MPI_Status status;
    for (int i = 0; i < 3; ++i)
    {
      MPI_Recv(&rec, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status); // 接受任意进程的消息
      printf("thread:%d %d\n", status.MPI_SOURCE, rec);                       // 输出源进程号
    }
  }
  else
  {
    MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
