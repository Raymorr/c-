#include "stack_node.h"

#define MAX_STACK_PRINT 3
#define TAB "      "

template <class T, template <class> class T1>
class Stack
{
private:
	SNode <T, T1> * top;
	int l;

public:
	Stack() { top = 0; l = 0; }
	~Stack() { delete_stack(); top = 0; l = 0; }
	void delete_stack() {
		SNode <T, T1> * curr = top;
		while (top) {
			curr = top;
			top = top->get_next();
			delete curr;
		}
		l = 0;
	}
	void operator==(const Stack& rhs) {
		top = rhs.top;
		l = rhs.l;
	}
	int operator<(const Stack& b) {
		return (*top < *b.top);
	}
	void clear() { top = 0; l = 0; }

	void push(SNode <T, T1> * n) { // add top
		n->set_next(top);
		top = n;
		l++;
	}
	void pop() { // delete top
		SNode <T, T1> * curr = top;
		if (top) {
			top = top->get_next();
			delete curr;
			l--;
		}
	}
	int size() const { return l; }
	SNode <T, T1> * get_top() const { return top; }
	void set_top(SNode <T, T1> * b) { top = b; }
	void set_l(int len) { l = len; }

	int read(FILE * fp, int n, int m) {
		T1 <T> curr;
		SNode <T, T1> * node;
		int i = 0, res = 0;
		for (; i < m; i++) {
			if ((res = curr.read(fp, n))) {
				return res;
			}
			node = new SNode <T, T1>;
			if (!node) return -1;
			*node == curr;
			push(node);
			curr.clear();
		}
		return 0;
	}

	int max_len() {
		int max = 0, i = 0, j = 0;
		SNode <T, T1> * curr = top;
		while (curr && j < MAX_STACK_PRINT) {
			j++;
			i = curr->len();
			if (i > max) max = i;
			curr = curr->get_next();
		}
		return max;
	}
	void print_curr(int level = 0) {
		int i = 0, j = 0, n = (l > MAX_STACK_PRINT) ? MAX_STACK_PRINT : l;
		int maxlen = max_len();
		SNode <T, T1> * curr = top;
		for (i = 0; i < level; i++) printf(TAB);
		printf(" "); for (i = 0; i < maxlen; i++) printf("_"); printf("_\n");
		for (i = 0; i < level; i++) printf(TAB); printf("| ");
		for (i = 0; i < maxlen; i++) printf(" "); printf("| <--\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < level; j++) printf(TAB);
			printf("| ");
			curr->print();
			for (j = curr->len(); j < maxlen; j++) printf(" ");
			printf("|\n");
			curr = curr->get_next();
		}
		for (i = 0; i < level; i++) printf(TAB);
		printf("|_"); for (i = 0; i < maxlen; i++) printf("_"); printf("|\n");
		//printf("\n");
	}
	void print(int level = 0) {
		if (!top) return;
		int i = 0, j = 0, n = (l > MAX_STACK_PRINT) ? MAX_STACK_PRINT : l;
		int maxlen = max_len();
		SNode <T, T1> * curr = top;
		for (i = 0; i < level; i++) printf(TAB);
		printf(" "); for (i = 0; i < maxlen; i++) printf("_"); printf("_\n");
		for (i = 0; i < level; i++) printf(TAB); printf("| ");
		for (i = 0; i < maxlen; i++) printf(" "); printf("|\n");
		for (i = 0; i < n; i++) {
			for (j = 0; j < level; j++) printf(TAB);
			printf("| ");
			curr->print();
			for (j = curr->len(); j < maxlen; j++) printf(" ");
			printf("|\n");
			curr = curr->get_next();
		}
		for (i = 0; i < level; i++) printf(TAB);
		printf("|_"); for (i = 0; i < maxlen; i++) printf("_"); printf("|\n");
		//printf("\n");
	}
	void help() {
		system("clear");
		printf("Stack\n\
 -1 - return\n\
  0 - goto top menu\n\
  1 - print Stack\n\
  2 - print size\n\
  3 - print top\n\
  4 - pop (delete top)\n\
  5 - push (add to top)\n\
  6 - delete all stack\n\
  7 - push n empty elements\n\n");
	}

	void add() {
		SNode <T, T1> * node = new SNode <T, T1>;
		if (!node) {
			printf("Not enough memory\n");
			return;
		}
		push(node);
	}
	void add_n() {
		SNode <T, T1> * node = 0;
		int n = 0, i = 0;
		printf("print n\n");
		if (scanf("%d", &n) != 1) return;
		for (i = 0; i < n; i++) {
			node = new SNode <T, T1>;
			if (!node) {
				printf("mem error\n");
				return;
			}
			push(node);
		}
	}
	void menu(int x = 0) {
		int i;
		system("clear");
		help();
		if (x) printf("Fill Stack with Queue with at least one Student\n");
		print();
		while (scanf("%d", &i) == 1) {
			help();
			if (x) printf("Fill Stack with Queue with at least one Student\n");
			switch(i) {
				case -1: return;
				case 0: if (top) top->menu(); help(); print(); break;
				case 1: print(); break;
				case 2: printf("SIZE = %d\n", size()); break;
				case 3: if (top) top->print(); break;
				case 4: pop(); print(); break;
				case 5: add(); print(); break;
				case 6: delete_stack(); break;
				case 7: add_n(); print(); break;
				default: return;
			}
		}
	}
};

