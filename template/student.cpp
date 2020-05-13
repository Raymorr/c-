#include "student.h"

void Student::help() {
	system("clear");
	printf("Student\n\
 -1 - return\n\
  0 - print student\n\
  1 - erase\n\
  2 - change student\n\n");
	print_();
}

void Student::add_new() {
	char buff[LEN];
	int k;
	printf("print name and value\n");
	while (scanf("%s%d", buff, &k) != 2) {
		printf("print name and value\n");
	}
	destroy();
	if ((k = init(buff, k))) {
		printf("error %d\n", k);
		return;
	}
}

void Student::menu() {
	int i;
	help();
	while (scanf("%d", &i) == 1) {
		switch(i) {
			case -1: return;
			case 0: break;
			case 1: destroy(); break;
			case 2: add_new(); break;
			default: return;
		}
		help();
	}
}

void Student::print() { printf("[%s %d] ", name, value); }
void Student::print_() { printf("[%s %d]\n", name, value); }

