//#pragma warning(disable : 4996) 
#ifndef HEADER5
#define HEADER5

#include <stack>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define LEN 1234
#define MP 5
using namespace std;

class record
{
private:
	char* name;
	int phone;
	int group;
public:
	record()
	{
		name = 0; phone = 0; group = 0;
	}
	~record()
	{
		destr();
	}
	record(const record& b)
	{
		init(b.name, b.phone, b.group);
	}
	record& operator=(const record& rhs)
	{
		destr();
		init(rhs.name, rhs.phone, rhs.group);
		return *this;
	}
	char* get_name() const { return name; }
	int get_phone() const { return phone;  }
	int get_group() const { return group; }

	int operator<(const record& b) const
	{
		if (name && b.name)
		{
			int res = strcmp(name, b.name);
			if (res) return res;
			if (phone - b.phone) return phone - b.phone;
			return group - b.group;
		}
		if (!name && b.name) return -1;
		if (name && !b.name) return 1;
		if (phone - b.phone) return phone - b.phone;
		return group - b.group;
	}

	int operator>(const record&b) const
	{
		if (name && b.name)
		{
			if(phone - b.phone) return phone - b.phone;
			int res = strcmp(name, b.name);
			if (res) return res;
			if (group - b.group) return group - b.group;
		}
		if(phone - b.phone) return phone - b.phone;
		if (!name && b.name) return -1;
		if (name && !b.name) return 1;
		return group - b.group;
	
	}

	int read(FILE* fp)
	{
		char buf[LEN];
		int v, g;
		if (fscanf(fp, "%s%d%d", buf, &v, &g) != 3) return 1;
	//	destr();
		return init(buf, v, g);
	}
	void print(int fd)
	{
		char buf[LEN];
		sprintf(buf, "%s\t%d\t%d\n", name, phone, group);
		int l = (int)strlen(buf);
		write(fd, &l, sizeof(int));
		write(fd, buf, l);
	}
	void destr()
	{
		delete[] name;
		name = 0;
		phone = 0;
		group = 0;
	}
	int init(const char* name_ = 0, int phone_ = 0, int group_ = 0)
	{
		if (name_ && !name)
		{
			name = new char[strlen(name_) + 1];
			if (!name) return -1;
			strcpy(name, name_);
		}
		phone = phone_;
		group = group_;
		return 0;
	}

};

#endif
