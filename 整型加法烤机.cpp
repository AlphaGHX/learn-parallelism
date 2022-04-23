#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#pragma comment(lib, "msmpi.lib")

int main(int argc, char **argv)
{
  int comm_sz, my_rank;
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int x;

  if (my_rank == 0)
  {
    while (1)
    {
      x += my_rank + 1;
    }
  }
  else
  {
    while (1)
    {
      x += my_rank + 1;
    }
  }

  MPI_Finalize();
  return 0;
}
