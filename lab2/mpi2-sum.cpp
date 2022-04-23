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
    int ans = 0, rec;
    for (int i = 1; i < 4; ++i)
    {
      int trx[] = {i * 25 + 1, (i + 1) * 25};          // 给定其他三个进程的计算范围
      MPI_Send(trx, 2, MPI_INT, i, 0, MPI_COMM_WORLD); // 向第i号进程发送计算范围
      MPI_Recv(&rec, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      ans += rec;
    }
    for (int i = 1; i <= 25; ++i) // 自己的计算范围
    {
      ans += i;
    }

    printf("%d\n", ans);
  }
  else
  {
    int trx[2], ans = 0;
    MPI_Recv(trx, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // 其他进程接受计算范围
    for (int i = trx[0]; i <= trx[1]; ++i)
    {
      ans += i;
    }
    MPI_Send(&ans, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  }

  MPI_Finalize();
  return 0;
}
