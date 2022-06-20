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
// 没有参数的初始化
MPI_Init(0, 0);
// 有参数的初始化
MPI_Init(&argc, &argv);

int MPI_Comm_size(MPI_Comm comm, int *size)
// 得到线程数存储在 comm_sz
MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

int MPI_Comm_rank(MPI_Comm comm, int *rank)
// 得到当前线程存储在 my_rank
MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
// 发送示例
MPI_Send("hello", 5 + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);


int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
// 接收示例
char msg[20];
MPI_Recv(msg, 20, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

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

// 内存共享
// 这样 buffer 就可以写东西进去，并且是共享内存，其他程序可以读取。
int shm_fd = shm_open("buffer", O_CREAT | O_RDWR, 0666);
ftruncate(shm_fd, 4096);
Buffer *buffer = (Buffer *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
// 这样就读取了 buffer 的数据，可以直接使用
int shm_fd = shm_open("buffer", O_RDWR, 0666);
Buffer *buffer = (Buffer *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

// 内存共享与信号量
// 这样就创建了一个初始值为 5 的信号量
sem_open("empty", O_CREAT, 0666, 5);
// 这样就读取了信号量，可以直接使用
sem_t *empty = sem_open("empty", O_RDONLY);
```

# OpenMP 系列

## 命令
* 编译：g++ test.cpp -o test.out -fopenmp
* 运行：./test.out

## 类型和函数定义
```cpp
// parallel 和 for 分开使用，解决有不同前置变量的需求，可以在for前得到一些值
#pragma omp parallel num_threads(thread_count) reduction(+ : sum) private(factor)
  {
    if ((omp_get_thread_num() * (n / thread_count)) % 2 == 0)
      factor = 1.0;
    else
      factor = -1.0;
#pragma omp for
    for (i = 0; i < n; i++) {
      sum += factor / (2 * i + 1);
      factor = -factor;
    }
  }
```

# 进程与信号系列

## 使用
```cpp
// signal
// 5秒后发送 SIGALRM 信号，signal 函数不会阻塞进程，然后由 sig_fun 函数处理。
void sig_fun(int sig);
alarm(5);
signal(SIGALRM, sig_fun);

// kill
// 给指定 pid 发送 SIGALRM 信号
kill(getppid(), SIGALRM);

// fork
// 复制子进程
pid_t pid;
pid = fork();
if (pid == 0) {
  // 子进程处理内容
} else {
  // 父进程处理内容
}
```
