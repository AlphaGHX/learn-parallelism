#include <iostream>

using namespace std;

struct list_node_s {
	int data;
	list_node_s *next;
};

list_node_s *head, *c;

void insert(int value) {
	list_node_s *t = new list_node_s();
	t->data = value;
	if (c->data == 0) {
		head = c = t;
	}
	c->next = t;
	c = t;
}

void print() {
	list_node_s *t = head;
	while (t) {
		cout << t->data << ' ';
		t = t->next;
	}
	cout << endl;
}

void del(int value) {
	list_node_s *t = head, *p = head;
	while (t) {
		if (t->data == value) {
			if (t == head) {
				head = t->next;
				delete p;
				return;
			}
			if (!t->next) {
				p->next = nullptr;
				c = p;
				delete t;
				return;
			}
			p->next = t->next;
			delete t;
			return;
		}
		p = t;
		t = t->next;
	}
}

void mem(int value) {
	list_node_s *t = head;
	while (t) {
		if (t->data == value) {
			cout << "true" << endl;
			return;
		}
		t = t->next;
	}
	cout << "false" << endl;
}

int main() {
	char op;
	int value;
	head = new list_node_s();
	c = new list_node_s();
	
	while(cin >> op) {
		if (op == 'i') {
			cin >> value;
			insert(value);
		} else if (op == 'd') {
			cin >> value;
			del(value);
		} else if (op == 'm') {
			cin >> value;
			mem(value);
		} else if (op == 'p') {
			print();
		} else {
			return 0;
		}
	}
	return 0;
}

