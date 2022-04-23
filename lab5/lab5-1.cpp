#include <pthread.h>
#include <sys/time.h>

#include <cstdlib>
#include <iostream>

#define ll long long

using namespace std;

pthread_mutex_t mutex;
ll sum;

struct Part {
  ll left;
  ll right;
};

void *add(void *argv) {
  Part *part = (Part *)argv;
  ll ans = 0;

  for (ll i = part->left; i <= part->right; ++i) {
    ans += i;
  }

  pthread_mutex_lock(&mutex);  // �ϲ�ʱ��Ҫ�����ۼ�sum
  sum += ans;
  pthread_mutex_unlock(&mutex);

  return 0;
}

int main(int argc, char **argv) {
  int threads = atoi(argv[1]);
  ll num = atoll(argv[2]);
  ll part = num / threads;
  double timeuse;
  timeval t1, t2;
  pthread_t *tid = (pthread_t *)malloc(threads * sizeof(pthread_t));
  Part *parts = (Part *)malloc(threads * sizeof(Part));
  pthread_mutex_init(&mutex, NULL);  // ��ʼ��������

  for (int i = 0; i < threads; ++i) {  // ������̼߳��㷶Χ
    parts[i].left = i == 0 ? 1 : i * part;
    parts[i].right = i == threads - 1 ? num : (i + 1) * part - 1;
  }

  gettimeofday(&t1, NULL);  // ���м��㿪ʼ

  for (int i = 0; i < threads; i++) {
    pthread_create(&tid[i], NULL, add, &parts[i]);
  }

  for (int i = 0; i < threads; i++) {
    pthread_join(tid[i], NULL);
  }

  gettimeofday(&t2, NULL);  // ���м������

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("����: \nSum  = %lld \nTime = %fms\n", sum, timeuse * 1000.0);

  sum = 0;

  gettimeofday(&t1, NULL);  // ���м��㿪ʼ

  for (int i = 1; i <= num; ++i) {
    sum += i;
  }

  gettimeofday(&t2, NULL);  // ���м������

  timeuse =
      (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec) / 1000000.0;

  printf("����: \nSum  = %lld \nTime = %fms", sum, timeuse * 1000.0);

  pthread_mutex_destroy(&mutex);

  return 0;
}
