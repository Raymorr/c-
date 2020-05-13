#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1024

class Student
{
private:
	char * name;
	int value;
public:
	Student(const char * n = 0, int v = 0) { init(n, v); }
	Student(const Student& i) { init(i.name, i.value); }
	~Student() { destroy(); }
	Student& operator=(const Student& rhs) {
		destroy();
		init(rhs.name, rhs.value);
		return *this;
	}
	void operator==(const Student& b) {
		name = b.name;
		value = b.value;
	}
	int operator<(const Student& b) const {
		if (name && b.name) {
			int res = strcmp(name, b.name);
			if (res) return res;
			return value - b.value;
		}
		if (!name && b.name) return -1;
		if (name && !b.name) return 1;
		return value - b.value;
	}
	void swap(Student& b) {
		char * tmp = name;
		name = b.name;
		b.name = tmp;
		int v = value;
		value = b.value;
		b.value = v;
	}
	const char * get_name() const { return name; }
	int get_value() const { return value; }
	int read(FILE * fp) {
		char buf[LEN];
		int v;
		if (fscanf(fp, "%s%d", buf, &v) != 2) return -2;
		destroy();
		return init(buf, v);
	}
	int init(const char * n = 0, int v = 0) {
		if (n) {
			name = new char[strlen(n) + 1];
			if (!name) return -1;
			strcpy(name, n);
		} else name = 0;
		value = v;
		return 0;
	}
	void destroy() {
		if (name) {
			delete [] name;
			name = 0;
		}
		value = 0;
	}
	void clear() {
		name = 0;
		value = 0;
	}

	void add_new();
	void print();
	void print_();
	void help();
	void menu();
};

