# 建议配置好环境后参加考试，丰富的类型提醒和补全将极大的帮助到你。

# MacOS环境
* brew install openmpi libomp

# MPI 系列

## 命令
* 编译：mpicxx test.cpp -o test.out
* 运行：mpiexec -oversubscribe -n 4 test.out

## 类型和函数定义
```cpp
MPI_Status status;

int MPI_Init(int *argc, char ***argv)

int MPI_Comm_size(MPI_Comm comm, int *size)

int MPI_Comm_rank(MPI_Comm comm, int *rank)

int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)

// 指定进程得到 recvbuf
int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)

// 每个进程都能得到 recvbuf
int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)

// root 号进程将 sendbuf 中的值按照每份 sendcount 个进行分组，然后发送到其他进程，其他进程可以使用 recvbuf 接收
int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)

// 其他进程将 sendbuf 发送到 root 号进程，root 号进程按照每份 recvcount 个进行组合，储存到 recvbuf
int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm)
```

# pthreads 系列

## 命令
* 编译：g++ test.cpp -o test.out -pthread
* 运行：./test.out

## 类型和函数定义
```cpp
pthread_mutex_t mutex;

sem_t sem;

int pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *)

int sem_init(sem_t *, int, unsigned int)

int pthread_create(_Nullable pthread_t *, const pthread_attr_t *, void *_Nullable (*)(void *), void *)

int pthread_join(pthread_t, void *_Nullable *)

int pthread_mutex_lock(pthread_mutex_t *)

int pthread_mutex_unlock(pthread_mutex_t *)

int sem_wait(sem_t *)

int sem_post(sem_t *)

int pthread_mutex_destroy(pthread_mutex_t *)

int sem_destroy(sem_t *)
```
