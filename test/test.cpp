#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <mpi.h>
#pragma comment(lib, "msmpi.lib")

using namespace std;

int main()
{
  int comm_sz, my_rank;
  MPI_Init(0, 0);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  int n = 8;

  vector<int> vx(n);
  vector<int> vy(n);
  vector<int> vz(n);

  if (my_rank == 0)
  {
    for (int i = 0; i < n; ++i)
      scanf(" %d", &vx[i]);
    for (int i = 0; i < n; ++i)
      scanf(" %d", &vy[i]);
  }

  vector<int> vrecx(2);
  vector<int> vrecy(2);

  MPI_Scatter(&vx, 2, MPI_INT, &vrecx, 2, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Scatter(&vy, 2, MPI_INT, &vrecy, 2, MPI_INT, 0, MPI_COMM_WORLD);

  vector<int> vans(2);

  for (int i = 0; i < 2; ++i)
    vans[i] = vx[i] + vy[i];

  MPI_Gather(&vans, 2, MPI_INT, &vz, 2, MPI_INT, 0, MPI_COMM_WORLD);

  if (my_rank == 0)
    for (int i = 0; i < n; ++i)
      printf("%d\n", vz[i]);

  MPI_Finalize();
  return 0;
}
