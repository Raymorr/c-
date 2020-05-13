#ifndef HEADER3
#define HEADER3

#include "comand.h"

void command::print_cmd(FILE *fp)
{
	if (type == CMD_NONE) return;
	if (type == QUIT)
	{
		fprintf(fp, "%s%s", "quit", ";\n");
		return;
	}
	if (type == STOP)
	{
		fprintf(fp, "%s%s", "stop", ";\n");
		return;
	}
	if (type == DELETE)
	{
		fprintf(fp, "%s", "delete where ");
		print_part(fp);
		if (oper)
		{
			if (oper == AND) fprintf(fp, "%s", " and ");
			if (oper == OR) fprintf(fp, "%s", " or ");
			print_part(fp);
		}
		fprintf(fp, "%s", ";\n");
	}
	if (type == SELECT)
	{
		fprintf(fp, "%s", "select * where ");
		print_part(fp);
		if (oper)
		{
			if (oper == AND) fprintf(fp, "%s", " and ");
			if (oper == OR) fprintf(fp, "%s", " or ");
			print_part(fp);
		}
		fprintf(fp, "%s", ";\n");
	}
	if (type == INSERT)
	{
		fprintf(fp, "%s%s%s%d", "insert (", this->get_name(), ", ", this->get_phone());
		fprintf(fp, "%s%d%s", ", ", this->get_group(), ");\n");	
	}
}

void command::print_part(FILE* fp)
{
	if (c_name != COND_NONE)
	{
		fprintf(fp, "%s", "name");
		if (c_name == EQ) fprintf(fp, "%s", " = ");
		else if (c_name == LIKE) fprintf(fp, "%s", " like ");
		else if (c_name == NE) fprintf(fp, "%s", " <> ");
		else if (c_name == LT) fprintf(fp, "%s", " < ");
		else if (c_name == GT) fprintf(fp, "%s", " > ");
		else if (c_name == LE) fprintf(fp, "%s", " <= ");
		else if (c_name == GE) fprintf(fp, "%s", " >= ");
		fprintf(fp, "%s", this->get_name());
		c_name = COND_NONE;
	}
	else if (c_phone != COND_NONE)
	{
		fprintf(fp, "%s", "phone");
		if (c_phone == EQ) fprintf(fp, "%s", " = ");
		else if (c_phone == LIKE) fprintf(fp, "%s", " like ");
		else if (c_phone == NE) fprintf(fp, "%s", " <> ");
		else if (c_phone == LT) fprintf(fp, "%s", " < ");
		else if (c_phone == GT) fprintf(fp, "%s", " > ");
		else if (c_phone == LE) fprintf(fp, "%s", " <= ");
		else if (c_phone == GE) fprintf(fp, "%s", " >= ");
		fprintf(fp, "%d", this->get_phone());
		c_phone = COND_NONE;
	}
	else if (c_group != COND_NONE)
	{
		fprintf(fp, "%s", "group");
		if (c_group == EQ) fprintf(fp, "%s", " = ");
		else if (c_group == LIKE) fprintf(fp, "%s", " like ");
		else if (c_group == NE) fprintf(fp, "%s", " <> ");
		else if (c_group == LT) fprintf(fp, "%s", " < ");
		else if (c_group == GT) fprintf(fp, "%s", " > ");
		else if (c_group == LE) fprintf(fp, "%s", " <= ");
		else if (c_group == GE) fprintf(fp, "%s", " >= ");
		fprintf(fp, "%d", this->get_group());
		c_group = COND_NONE;
	}
}
int command::sep(int &m, char*& str)
{
	int p = this->get_phone() , g = this->get_group(), pf = 0, gf = 0, nf = 0, f = 0;
	char* name = this->get_name();

	if (!strcmp(str, "name"))
	{
		nf = 1;
		f = 1;
	}
	if (!strcmp(str, "phone"))
	{
		pf = 1;
		f = 1;
	}
	if (!strcmp(str, "group"))
	{
		gf = 1;
		f = 1;
	}

	if (!f) return -3;
	f = 0;

	str = 1 + strchr(str, 0);
	m--;

	if (nf)
	{
		if (!strcmp(str, "=")) c_name = EQ;
		else if (!strcmp(str, "<>")) c_name = NE;
		else if (!strcmp(str, "<=")) c_name = LE;
		else if (!strcmp(str, ">=")) c_name = GE;
		else if (!strcmp(str, "<")) c_name = LT;
		else if (!strcmp(str, "like")) c_name = LIKE;
		else if (!strcmp(str, ">")) c_name = GT;
	}
	if (gf)
	{
		if (!strcmp(str, "=")) c_group = EQ;
		else if (!strcmp(str, "<>")) c_group = NE;
		else if (!strcmp(str, "<=")) c_group = LE;
		else if (!strcmp(str, ">=")) c_group = GE;
		else if (!strcmp(str, "<")) c_group = LT;
		else if (!strcmp(str, "like")) c_group = LIKE;
		else if (!strcmp(str, ">")) c_group = GT;
	}
	if (pf)
	{
		if (!strcmp(str, "=")) c_phone = EQ;
		else if (!strcmp(str, "<>")) c_phone = NE;
		else if (!strcmp(str, "<=")) c_phone = LE;
		else if (!strcmp(str, ">=")) c_phone = GE;
		else if (!strcmp(str, "<")) c_phone = LT;
		else if (!strcmp(str, "like")) c_phone = LIKE;
		else if (!strcmp(str, ">")) c_phone = GT;
	}
	if (c_phone == COND_NONE && c_group == COND_NONE && c_name == COND_NONE) return -4;
	str = 1 + strchr(str, 0);
	m--;

	if (nf)
	{
		name = str;
		if (!m)
		{
			char *v = strchr(name, ';');
			if (!v) return -100;
			*v = 0;
		}
		f = 1;
	}
	if (pf)
	{
		if (!m)
		{
			char *v = strchr(str, ';'); 
			if (!v) return -100;
			*v = 0;
		}
		p = atoi(str);
		f = 1;
	}
	if (gf)
	{
		if (!m)
		{
			char *v = strchr(str, ';');
			if (!v) return -100;
			*v = 0;
		}
		g = atoi(str);
		f = 1;
	}
	if (!f) return -5;
//	if(get_name() || get_group() || get_phone()) destr()
	this->init(name, p, g);
	return 0;
}
int command::parse(char* str)
{
	for(int i=0;str[i];i++)if(str[i]=='\n'){str[i]=0;break;}
	char *str2, *str1 = str;
	int m = 0;
	str2 = str;
	while ((str = strchr(str2, ' ')) != 0)
	{
		if (str == str2) return -1;
		*str = 0;
		m++;
		str2 = str + 1;
	}
	str = str1;

	if (!strcmp(str, "quit;"))
	{
		type = QUIT;
		return 1;
	}
	else if (!strcmp(str, "stop;"))
	{
		type = STOP;
		return 1;
	}
	else if (!strcmp(str, "delete"))
	{
		type = DELETE;
		if (!m) return -4;
		str = 1 + strchr(str, 0);
		m--;
		if (!m) return -4;
		if (strcmp(str, "where")) return -2;
		str = 1 + strchr(str, 0);
		m--;
		if (this->sep(m, str)) return -3;
		if (!m) return 0;
		str = 1 + strchr(str + 1, 0);
		m--;
		if (!strcmp(str, "and")) oper = AND;
		else if (!strcmp(str, "or")) oper = OR;
		else return -123;
		str = 1 + strchr(str + 1, 0);
		m--;
		if (this->sep(m, str)) return -3;
	}
	else if (!strcmp(str, "select"))
	{
		type = SELECT;
		if (!m) return -4;
		str = 1 + strchr(str, 0);
		m--;
		if (!m) return -4;
		if (strcmp(str, "*")) return -2;
		str = 1 + strchr(str, 0);
		m--;
		if (strcmp(str, "where")) return -3;
		str = 1 + strchr(str, 0);
		m--;
		if (this->sep(m, str)) return -3;
		if (!m) return 0;
		str = 1 + strchr(str + 1, 0);
		m--;
		if (!strcmp(str, "and")) oper = AND;
		else if (!strcmp(str, "or")) oper = OR;
		else return -123;
		str = 1 + strchr(str + 1, 0);
		m--;
		if (this->sep(m, str)) return -3;
	}
	else if (!strcmp(str, "insert"))
	{
		if (m != 3) return -1;
		type = INSERT;
		char* name = 0;
		int p = 0, g = 0;
		str = 1 + strchr(str, 0);
		if (*(str) != '(') return -2;
		str++;
		name = str;
		str = 1 + strchr(str, 0);
		if (*(str - 2) != ',') return -3;
		*(str - 2) = 0;
		char* temp = str;
		str = 1 + strchr(str, 0);
		if (*(str - 2) != ',') return -3;
		*(str - 2) = 0;
		p = atoi(temp);
		temp = str;
		str = strchr(str, ')');
		if (!str) return -2;
		if (*(str + 1) != ';') return -4;
		(*str) = 0;
		g = atoi(temp);
		this->init(name, p, g);
	}
	return 0;
}


#endif
