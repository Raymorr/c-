#include "tree.h"
#include <time.h>

int read(Tree <Student, Queue, Stack> *, const char *, int, int, int);
int read(Stack <Student, Queue> *, const char *, int, int);
int read(Queue <Student> *, const char *, int);

int main(int argc, char ** argv) {
	Tree <Student, Queue, Stack> a;
//	Stack <Student, Queue> a;
//	Queue <Student> a;
	int n, m, k, res;
	const char * filename = "a.txt";

	if (argc < 4 || argc > 5 || (n = atoi(argv[1])) <= 0
							|| (m = atoi(argv[2])) <= 0
							|| (k = atoi(argv[3])) <= 0) {
		printf("usage: %s [n] [m] [k] [filename]\n", argv[0]);
		return -4;
	}
	if (argc == 5) filename = argv[4];
	else printf("file %s is default\n", filename);

	if ((res = read(&a, filename, n, m, k))) {
		switch (res) {
			case -1:
				printf("Not enough memory\n");
				break;
			case -2:
				printf("Cannot read file %s\n", filename);
				break;
			case -3:
				printf("Cannot open file %s\n", filename);
				break;
			default:
				printf("Unknown error\n");
		}
		return -2;
	}

//	a.print();
	a.menu();

	return 0;
}

int read(Tree <Student, Queue, Stack> * a, const char * name, int n, int m, int k) {
	int res;
	FILE * fp;
	if (!(fp = fopen(name, "r"))) return -3;
	res = a->read(fp, n, m, k);
	fclose(fp);
	return res;
}

int read(Stack <Student, Queue> * a, const char * name, int n, int m) {
	int res;
	FILE * fp;
	if (!(fp = fopen(name, "r"))) return -3;
	res = a->read(fp, n, m);
	fclose(fp);
	return res;
}

int read(Queue <Student> * a, const char * name, int n) {
	int res;
	FILE * fp;
	if (!(fp = fopen(name, "r"))) return -3;
	res = a->read(fp, n);
	fclose(fp);
	return res;
}

