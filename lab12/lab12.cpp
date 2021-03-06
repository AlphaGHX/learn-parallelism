#include <iostream>

using namespace std;

struct list_node_s {
  int data;
  list_node_s *next;

  list_node_s(int a, list_node_s *b) : data(a), next(b) {}
};

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
  cout << "NOT FOUND" << endl;
  return;
}

void mem(int value) {
  list_node_s *t = head;
  while (t) {
    if (t->data == value) {
      cout << "FOUND" << endl;
      return;
    }
    t = t->next;
  }
  cout << "NOT FOUND" << endl;
  return;
}

int main() {
  char op;
  int value;

  while (cin >> op) {
    switch (op) {
      case 'i':
        cin >> value;
        insert(value);
        break;
      case 'd':
        cin >> value;
        del(value);
        break;
      case 'm':
        cin >> value;
        mem(value);
        break;
      case 'p':
        print();
        break;
      default:
        return 0;
    }
  }
  return 0;
}
