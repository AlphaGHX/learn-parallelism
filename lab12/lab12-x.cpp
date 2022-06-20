#include <iostream>
#include <pthread.h>
#include <ctime>
#include <unistd.h>

using namespace std;

struct list_node_s {
  int data;
  list_node_s *next;

  list_node_s(int a, list_node_s *b) : data(a), next(b) {}
};

pthread_rwlock_t rwlock;

list_node_s *head, *c;
int len;

void insert(int value) {
  list_node_s *t = new list_node_s(value, nullptr);
  if (!len) {
    head = c = t;
    len++;
    return;
  }
  c->next = t;
  c = t;
  len++;
  return;
}

void print() {
  if (!len) {
    cout << "NULL" << endl;
    return;
  }
  list_node_s *t = head;
  cout << "p: ";
  while (t) {
    cout << t->data << ' ';
    t = t->next;
  }
  cout << endl;
  return;
}

void del(int value) {
  list_node_s *t = head, *p = head;
  while (t) {
    if (t->data == value) {
      cout << "d: " << t->data << endl;
      if (t == head) {
        head = t->next;
        delete p;
        len--;
        return;
      }
      if (!t->next) {
        p->next = nullptr;
        c = p;
        delete t;
        len--;
        return;
      }
      p->next = t->next;
      delete t;
      len--;
      return;
    }
    p = t;
    t = t->next;
  }
  return;
}

void mem(int value) {
  list_node_s *t = head;
  while (t) {
    if (t->data == value) {
      cout << "f: " << t->data << endl;
      return;
    }
    t = t->next;
  }
  return;
}

void *findThread(void *arg) {
  int val;
  while (1) {
    val = (rand() % 91) + 10;
    pthread_rwlock_rdlock(&rwlock);
    mem(val);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  }
  return nullptr;
}

void *delThread(void *arg) {
  int val;
  while (1) {
    val = (rand() % 91) + 10;
    pthread_rwlock_wrlock(&rwlock);
    del(val);
    pthread_rwlock_unlock(&rwlock);
    sleep(1);
  }
  return nullptr;
}

void *printThread(void *arg) {
  while (1) {
    pthread_rwlock_rdlock(&rwlock);
    print();
    pthread_rwlock_unlock(&rwlock);
    sleep(10);
  }
  return nullptr;
}

// insert(int value);
// del(int value);
// mem(int value);
// print();

int main() {
  char op;
  int value;
  
  srand((unsigned)time(NULL));

  pthread_t tid0, tid1, tid2;

  pthread_rwlock_init(&rwlock, NULL);
  
  for (int i = 1; i <= 10; i++) {
    insert(i * 10);
  }

  pthread_create(&tid0, NULL, findThread, NULL);
  pthread_create(&tid1, NULL, delThread, NULL);
  pthread_create(&tid2, NULL, printThread, NULL);
  
  pthread_join(tid0, NULL);
  
  return 0;
}
