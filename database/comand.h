#ifndef HEADER4
#define HEADER4
#include "record.h"

enum cmd_type
{
	CMD_NONE, QUIT, STOP, SELECT, INSERT, DELETE
};
enum cond_type
{
	COND_NONE, EQ, NE, LT, GT, LE, GE, LIKE
};
enum op_type
{
	OP_NONE, AND, OR
};


class command : public record
{
private:
	cmd_type type = CMD_NONE;
	cond_type c_name = COND_NONE;
	cond_type c_phone = COND_NONE;
	cond_type c_group = COND_NONE;
	op_type oper = OP_NONE;
public:
	command() : record() {};
	~command()  { destr(); };
	void print_part(FILE*);
	void print_cmd(FILE*);
	int sep(int &m, char*& str);
	int parse(char* str);
	cmd_type get_type() { return type; }
	cond_type get_c_name() { return c_name; }
	cond_type get_c_phone() { return c_phone; }
	cond_type get_c_group() { return c_group; }
	op_type get_oper() { return oper; }
};

#endif
