#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>
#define ll long long
#pragma comment(lib, "msmpi.lib")

int main(int argc, char **argv)
{
  // dev test
  int comm_sz, my_rank;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  ll num = atoll(argv[1]); // 获取参数
  ll part = num / comm_sz; // 分割计算任务
  double partAns = 0;
  double ans = 0;
  ll x = 1;       // 除数
  short flag = 1; // 符号
  double startTime, endTime;

  if (my_rank == 0)
  {
    ll start = (comm_sz - 1) * part + 1;
    flag = start & 1 ? flag : -flag;
    x += (start - 1) << 1;
    startTime = MPI_Wtime();
    // printf("p%lld: s %lld e %lld flag %d x %lld\n", my_rank, start, num, flag, x);
    for (ll i = start; i <= num; ++i)
    {
      partAns += double(flag) / double(x);
      flag = -flag;
      x += 2;
    }
  }
  else
  {
    ll start = (my_rank - 1) * part + 1;
    flag = start & 1 ? flag : -flag;
    x += (start - 1) << 1;
    // printf("p%lld: s %lld e %lld flag %d x %lld\n", my_rank, start, start + part - 1, flag, x);
    for (ll i = start; i <= start + part - 1; ++i)
    {
      partAns += double(flag) / double(x);
      flag = -flag;
      x += 2;
    }
  }

  // printf("\t%0.20f\n", partAns);

  MPI_Reduce(&partAns, &ans, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (my_rank == 0)
  {
    endTime = MPI_Wtime();
    printf("extra process:\t%lld\npi:\t\t%.10f\ntime:\t\t%.10fms\n", num - comm_sz * part, ans * 4, (endTime - startTime) * 1000);
  }

  MPI_Finalize();
  return 0;
}

// pi: 3.1415926535897932384626433832795028841971693993