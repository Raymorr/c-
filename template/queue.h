#include "queue_node.h" 

#define MAX_QUEUE_PRINT 3

template <class T>
class Queue
{
private:
	QNode <T> * head, * tail;
	int l;

	void destroy() {
		QNode <T> * curr = 0;
		while (head) {
			curr = head;
			head = head->get_next();
			delete curr;
		}
		head = tail = 0;
		l = 0;
	}

public:
	Queue() { head = tail = 0; l = 0; }
	~Queue() { destroy(); }
	void operator==(const Queue& rhs) {
		head = rhs.head;
		tail = rhs.tail;
		l = rhs.l;
	}
	int operator<(const Queue& b) {
		return (*head < *b.head);
	}
	void clear() { head = tail = 0; l = 0; }

	void push(QNode <T> * n) { // add to tail
		if (!head) head = n;
		else tail->set_next(n);
		tail = n;
		l++;
	}
	void pop() { // delete head
		QNode <T> * curr = head;
		if (head) {
			head = head->get_next();
			delete curr;
			if (!head) tail = 0;
			l--;
		}
	}
	int size() const { return l; }
	QNode <T> * get_head() const { return head; }
	QNode <T> * get_tail() const { return tail; }

//	int read(FILE *, int);
	int read(FILE * fp, int n) {
		T curr;
		QNode <T> * node;
		int i = 0, res = 0;
		for (; i < n; i++) {
			if ((res = curr.read(fp))) {
				return res;
			}
			node = new QNode <T>;
			if (!node) return -1;
			*node == curr;
			push(node);
			curr.clear();
		}

		return 0;
	}

	int number_len(int a) {
		int k = 0;
		if (a < 0) k++;
		if (a == 0) return 1;
		while (a) {
			k++;
			a /= 10;
		}
		return k;
	}
	int len() {
		int s = 0, j = 0;
		QNode <T> * curr = head;
		while (curr && j < MAX_QUEUE_PRINT) {
			j++;
			if (!curr->get_name()) s += 11;
			else s += strlen(curr->get_name()) + 4 + number_len(curr->get_value());
			curr = curr->get_next();
		}
		return s;
	}
	void print() {
		if (!head) return;
		int i = 0, n = (l > MAX_QUEUE_PRINT) ? MAX_QUEUE_PRINT : l;
		QNode <T> * curr = head;
		for (; i < n; i++) {
			curr->print();
			curr = curr->get_next();
		}
	}
	void print_() {
		if (!head) return;
		int i = 0, n = (l > MAX_QUEUE_PRINT) ? MAX_QUEUE_PRINT : l;
		QNode <T> * curr = head;
		for (; i < n; i++) {
			curr->print();
			curr = curr->get_next();
		}
		printf("\n");
	}

	void help() {
		system("clear");
		printf("Queue\n\
 -1 - return\n\
  0 - goto head menu\n\
  1 - goto tail menu\n\
  2 - print Queue\n\
  3 - print size\n\
  4 - print head\n\
  5 - print tail\n\
  6 - pop (delete head)\n\
  7 - push (add to tail)\n\
  8 - push n empty elements\n\
  9 - delete all queue\n\n");
	}

	void add() {
		QNode <T> * node = new QNode <T>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		printf("Print name and value\n");
		if (node->read(stdin)) {
			char buf[LEN];
			scanf("%s", buf);
			delete node;
			return;
		}
		push(node);
	}
	void add_n() {
		QNode <T> * node = 0;
		int n = 0, i = 0;
		printf("print n\n");
		if (scanf("%d", &n) != 1) return;
		for (i = 0; i < n; i++) {
			node = new QNode <T>;
			if (!node) {
				printf("mem error\n");
				return;
			}
			push(node);
		}
	}
	void menu() {
		int i, k = 0;
		help();
		print_();
		while (scanf("%d", &i) == 1) {
			k = 0;
			switch(i) {
				case -1: system("clear"); return;
				case 0: if (head) head->menu(); break;
				case 1: if (tail) tail->menu(); break;
				case 2: break;
//				case 3: printf("SIZE = %d\n\n", size()); break;
//				case 4: head->print_(); printf("\n"); break;
//				case 5: tail->print_(); printf("\n"); break;
				case 6: pop(); break;
				case 7: add(); break;
				case 8: add_n(); break;
				case 9: destroy(); break;
			}
			help();
			print_();
			switch(i) {
				case 3: printf("SIZE = %d\n\n", size()); break;
				case 4: if (head) head->print_(); printf("\n"); break;
				case 5: if (tail) tail->print_(); printf("\n"); break;
			}
		}
	}
};

