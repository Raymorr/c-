#ifndef HEADER1
#define HEADER1

#include "comand.h"
#define LEN 1234
static int s = 0;

////// node
template <class T>
class lnode : public T
{
private:
	lnode *next;
	lnode *prev;
public:
	lnode()
	{
		next = 0;
		prev = 0;
	}
	lnode(const lnode& i) : T(i)
	{
		next = 0;
		prev = 0; 
	}
	lnode& operator=(const T &rhs)
	{
		(*(T*)(this)) = rhs;
		next = 0;
		prev = 0;
		return *this;
	}
	~lnode() 
	{
		prev = 0;
		next = 0;
	}
	lnode *get_next() const
	{
		return next;
	}
	void set_next(lnode * next)
	{
		this->next = next;
	}
	lnode *get_prev() const
	{
		return prev;
	}
	void set_prev(lnode * prev)
	{
		this->prev = prev;
	}

};

static int srch = 0;
////////////////////////////////////////////////////////////////
template <class T>
class avlnode
{
private:
	lnode<T>* data;
	int balance;
	avlnode *left, *right;
public:
	avlnode<T>()
	{
		right = 0;
		left = 0;
		balance = 0;
	}
	avlnode<T>(const avlnode<T>& i)
	{
		left = 0;
		right = 0;
		balance = 0;
	}
	~avlnode<T>()
	{
		left = 0;
		right = 0;
		balance = 0;
		data = 0;
	}
	avlnode<T> *get_right() const
	{
		return right;
	}
	void set_right(avlnode<T>* right)
	{
		this->right = right;
	}
	avlnode<T> *get_left() const
	{
		return left;
	}
	void set_left(avlnode<T> *left)
	{
		this->left = left;
	}
	int get_balance() const
	{
		return balance;
	}
	void set_balance(int v)
	{
		balance = v;
	}
	lnode<T> *get_data() const
	{
		return data;
	}
	void set_data(lnode<T> *data)
	{
		this->data = data;
	}
	
				
	////////
	avlnode<T> *addn(avlnode<T>* x, avlnode<T> *root, int *grow)
	{
		int incr = 0;
		*grow = 0; 
		if (root && srch == -2 && (*(x->get_data()) < *(root->get_data())) == 0) 
		{
			srch = 1;
			return 0;
		}
		if(!root)
		{
			x->set_left(0); x->set_right(0);
			x->set_balance(0);
			*grow = 1;
			root = x;
			return root;
		}
		if ((*(x->get_data()) < *(root->get_data())) < 0)
		{
			avlnode<T> *t =  addn(x, root->get_left(), &incr);
			if (srch == 1) return 0;
			root->set_left(t);
			if (incr)
			{
				switch (root->get_balance())
				{
				case 0: 
					root->set_balance(-1);
					*grow = 1; break;
				case 1: root->set_balance(0); break;
				case -1:
					switch (root->get_left()->get_balance())
					{
						case -1: root = Rebuild_L1(root); break;
						case 1: root = Rebuild_L2(root);
					}
				}
			}
		}
		else
		{
			avlnode<T> *t = addn(x, root->get_right(), &incr);
			if (srch == 1) return 0;
			root->set_right(t);
			if (incr)
			{
				switch (root->get_balance())
				{
				case 0: root->set_balance(1);
					*grow = 1; break;
				case -1: root->set_balance(0); break;
				case 1:
					 switch (root->get_right()->get_balance())
					{
						case 1: root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root);
					}
				}
			} 
		}
	return root;
	}

	avlnode<T> *addg(avlnode<T>* x, avlnode<T> *root, int *grow)
	{
		int incr = 0;
		*grow = 0; 
		if(!root)
		{
			x->set_left(0); x->set_right(0);
			x->set_balance(0);
			*grow = 1;
			root = x;
			return root;
		}
		if ((*(x->get_data()) > *(root->get_data())) <= 0)
		{
			root->set_left(addg(x, root->get_left(), &incr));
			if (incr)
			{
				switch (root->get_balance())
				{
				case 0: 
					root->set_balance(-1);
					*grow = 1; break;
				case 1: root->set_balance(0); break;
				case -1:
					switch (root->get_left()->get_balance())
					{
						case -1: root = Rebuild_L1(root); break;
						case 1: root = Rebuild_L2(root);
					}
				}
			}
		}
		else
		{
			root->set_right(addg(x, root->get_right(), &incr));
			if (incr)
			{
				switch (root->get_balance())
				{
				case 0: root->set_balance(1);
					*grow = 1; break;
				case -1: root->set_balance(0); break;
				case 1:
					 switch (root->get_right()->get_balance())
					{
						case 1: root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root);
					}
				}
			} 
		}
	return root;
	}

	avlnode<T>* Rebuild_L1 (avlnode<T>* a)
	{
		avlnode<T> *b;
		b = a->get_left();
		a->set_left(b->get_right());
		b->set_right(a);
		if(b->get_balance())
		{
			a->set_balance(0);
			b->set_balance(0);
		}
		else
		{
			a->set_balance(-1);
			b->set_balance(1); 
		}
		return b;
	}
	
	avlnode<T>* Rebuild_R1(avlnode<T>* a)
	{
		avlnode<T> *b;
		b = a->get_right();
		a->set_right(b->get_left());
		b->set_left(a);
		if (b->get_balance())
		{
			a->set_balance(0);
			b->set_balance(0);
		}
		else
		{
			a->set_balance(1);
			b->set_balance(-1);
		}
		return b;
	}

	avlnode<T>* Rebuild_L2 (avlnode<T> *a)
	{
		avlnode<T> *b, *c;
		b = a->get_left();
		c = b->get_right();
		a->set_left(c->get_right());
		b->set_right(c->get_left());
		c->set_left(b);
		c->set_right(a);
		switch(c->get_balance())
		{
		case 0:
		 a->set_balance(0);
		 b->set_balance(0);
		 break;
		 case -1:
		 a->set_balance(1);
		 b->set_balance(0);
		 break;
		 case 1:
		 a->set_balance(0);
		 b->set_balance(-1);
		}
		c->set_balance(0); 
		return c;
	}
	
	avlnode<T>* Rebuild_R2(avlnode<T> *a)
	{
		avlnode<T> *b, *c;
		b = a->get_right();
		c = b->get_left();
		a->set_right(c->get_left());
		b->set_left(c->get_right());
		c->set_left(a);
		c->set_right(b);
		switch (c->get_balance())
		{
		case 0:
			a->set_balance(0);
			b->set_balance(0);
			break;
		case -1:
			a->set_balance(0);
			b->set_balance(1);
			break;
		case 1:
			a->set_balance(-1);
			b->set_balance(0);
		}
		c->set_balance(0);	
		return c;	
	}
	
	avlnode<T> *deln (lnode<T>* x, avlnode<T>* root, int *grow, int* big = 0, lnode<T> *dd = 0)
	{
		int incr;
		avlnode<T> *pos; 
		*grow =0;
		if (!root) return 0; 
		if ((*x < *root->get_data()) == 0)
		{
			if ((root->get_left()) == 0)
			{ 
				*grow = -1;
				pos = root->get_right();
				if(*big) 
				{
					if(dd) delete dd;
					else delete root->get_data();
				}
				delete root;
				return pos;
			}
			if ((root->get_right()) == 0)
			{
				*grow = -1;
				pos = root->get_left();
				if(*big) 
				{
					if(dd) delete dd;
					else delete root->get_data();
				}
				delete root;
				return pos; 
			}
			for (pos =root->get_left(); pos->get_right();) pos = pos->get_right();	
			if(*big)
			{
				lnode<T> *q = root->get_data();
						root->set_data(pos->get_data());	
			root->set_left(deln(pos->get_data(), root->get_left(), &incr, big, q));

			}
			else
			{
				 lnode<T>*q = 0;
			root->set_data(pos->get_data());	
			root->set_left(deln(pos->get_data(), root->get_left(), &incr, big, q));
			}
			if (incr)
			{
				switch (root->get_balance())
				{
					case -1: root->set_balance(0); *grow =-1; break;
					case 0: root->set_balance(1); break;
					case 1:
					switch (root->get_right()->get_balance())
					{
						case 1: *grow = -1; //
						case 0: root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root); 
						*grow=-1;
					}
				}
			}
		}
		else
		{
			if ((*x < *root->get_data()) < 0)
			{
				root->set_left(deln(x, root->get_left(), &incr, big, dd));
				if (incr)
				{
					switch (root->get_balance())
					{
					case -1: root->set_balance(0); *grow = 1; break;
					case 0: root->set_balance(1); break;
					case 1:
						switch (root->get_right()->get_balance())
						{
							case 1: *grow = -1; //
							case 0: root = Rebuild_R1(root); break;
							case -1: root = Rebuild_R2(root); *grow = -1;
						}
					}
				}
			}
			else
			{
				root->set_right(deln(x, root->get_right(), &incr, big, dd));
				if (incr)
				{
					switch (root->get_balance())
					{
					case 1: root->set_balance(0); *grow = -1; break;
					case 0: root->set_balance(-1); break;
					case -1:
						switch (root->get_left()->get_balance())
						{
						case -1: *grow = -1; //
						case 0: root = Rebuild_L1(root); break;
						case 1: root = Rebuild_L2(root); *grow = -1;
						}
					}
				}
			}
		}
		
		return root;
	}

	avlnode<T> *delg (lnode<T>* x, avlnode<T>* root, int *grow)
	{
		int incr;
		avlnode<T> *pos; 
		*grow =0;
		if (!root) return 0; 
		if ((*x > *root->get_data()) == 0)
		{
			if ((root->get_left()) == 0)
			{ 
				*grow = -1;
				pos = root->get_right();
				delete root;
				return pos;
			}
			if ((root->get_right()) == 0)
			{
				*grow = -1;
				pos = root->get_left();
				delete root;
				return pos; 
			}
			for (pos =root->get_left(); pos->get_right();) pos = pos->get_right();
			root->set_data(pos->get_data());
			root->set_left(delg(pos->get_data(), root->get_left(), &incr));
			if (incr)
			{
				switch (root->get_balance())
				{
					case -1: root->set_balance(0); *grow =-1; break;
					case 0: root->set_balance(1); break;
					case 1:
					switch (root->get_right()->get_balance())
					{
						case 1: *grow = -1; //
						case 0: root = Rebuild_R1(root); break;
						case -1: root = Rebuild_R2(root); 
						*grow=-1;
					}
				}
			}
		}
		else
		{
			if ((*x > *root->get_data()) < 0)
			{
				root->set_left(delg(x, root->get_left(), &incr));
				if (incr)
				{
					switch (root->get_balance())
					{
					case -1: root->set_balance(0); *grow = 1; break;
					case 0: root->set_balance(1); break;
					case 1:
						switch (root->get_right()->get_balance())
						{
							case 1: *grow = -1; //
							case 0: root = Rebuild_R1(root); break;
							case -1: root = Rebuild_R2(root); *grow = -1;
						}
					}
				}
			}
			else
			{
				root->set_right(delg(x, root->get_right(), &incr));
				if (incr)
				{
					switch (root->get_balance())
					{
					case 1: root->set_balance(0); *grow = -1; break;
					case 0: root->set_balance(-1); break;
					case -1:
						switch (root->get_left()->get_balance())
						{
						case -1: *grow = -1; //
						case 0: root = Rebuild_L1(root); break;
						case 1: root = Rebuild_L2(root); *grow = -1;
						}
					}
				}
			}
		}
		
		return root;
	}

};


//////////////
template <class T>
class avl
{
private:
	avlnode<T> *curr, *head;
public:
	avl()
	{
		head = 0;
		curr = 0;
	}
	avl(const avl& i)
	{
		head = i.head;
		curr = i.curr;
	}
	~avl()
	{
	}
	
	void set_curr(avlnode<T>* c)
	{
		curr = c;
	}
	void set_head(avlnode<T>* c)
	{
		head = c;
	}
	avlnode<T>* get_curr(void)
	{
		return curr;
	}
	avlnode<T>* get_head(void)
	{
		return head;
	}
	void a_delete(void)
	{
		avlnode<T> *tmp = curr;
		//if(!head) return;
		if (curr->get_left())
		{
			curr = curr->get_left();
			a_delete();
			curr = tmp;
		}
		if (curr->get_right())
		{
			curr = curr->get_right();
			a_delete();
			curr = tmp;
		}
		delete curr;
		curr = 0;
	}
	void a_print(avlnode<T> * root, int fd)
	{
		if (!root) return;
		root->get_data()->print(fd);
		if (root->get_left())
		{
			a_print(root->get_left(), fd);
		}
		if (root->get_right())
		{
			a_print(root->get_right(), fd);
		}
	}

	void a_stack(avlnode<T> * root, stack<lnode<T>*>* ms)
	{
		if (!root) return;
		ms->push(root->get_data());
		if (root->get_left())
		{
			a_stack(root->get_left(), ms);
		}
		if (root->get_right())
		{
			a_stack(root->get_right(), ms);
		}
	}
	int a_readn(lnode<T> *h)
	{
		avlnode<T> *root = new avlnode<T>;
		if (!root) { return -1; }
		root->set_data(h);
		head = root;
		curr = head;
		head->set_balance(0);
		head->set_left(0);
		head->set_right(0);
		h = h->get_next();
		while (h)
		{
			avlnode<T> *tmp = new avlnode<T>;
			if (!tmp) return -3;
	
			tmp->set_data(h);
			int i = 0;
			head = head->addn(tmp, head, &i);
			h = h->get_next();
		}
		return 0;
	}

	int a_readg(lnode<T> *h)
	{
		avlnode<T> *root = new avlnode<T>;
		if (!root) { return -1; }
		root->set_data(h);
		head = root;
		curr = head;
		head->set_balance(0);
		head->set_left(0);
		head->set_right(0);
		h = h->get_next();
		while (h)
		{
			avlnode<T> *tmp = new avlnode<T>;
			if (!tmp) return -3;

			tmp->set_data(h);
			int i = 0;
			head = head->addg(tmp, head, &i);
			h = h->get_next();
		}
		return 0;
	}

};
////////////////////////////////////////////////////////////////
////// list
template <class T>
class list
{
private:
	avl<T> srchn, srchg;
	lnode<T> *head, *curr;
public:
	int gr = 0;
	list(lnode<T> * node = 0)
	{
		head = node;
		curr = node;
	}
	list(const list& i)
	{
		head = i.head;
		curr = i.curr;
	}
	list& operator=(const list&rhs)
	{
		head = rhs.curr;
		curr = rhs.curr;
		return *this;
	}
	int operator<(list&rhs) 
	{ 
		if(gr && rhs.gr) return rhs.gr - gr;
		if(head && rhs.head)
		{
			return rhs.head->get_group() - head->get_group();
		}
		if(head && !rhs.head) return -1;
		else return 1;
	}
	~list()
	{
//		l_delete();
		head = 0;
		curr = 0;
	}
	avl<T> get_avln()
	{
		return srchn;
	}	
	avl<T> get_avlg()
	{
		return srchg;
	}
	void set_havln(avlnode<T>* tmp)
	{
		srchn.set_head(tmp);
	}
	void set_cavln(avlnode<T>* tmp)
	{
		srchn.set_curr(tmp);
	}
	void set_havlg(avlnode<T>* tmp)
	{
		srchg.set_head(tmp);
	}
	void set_cavlg(avlnode<T>* tmp)
	{
		srchg.set_curr(tmp);
	}
	lnode<T> * get_head() const
	{
		return head;
	}
	void set_head(lnode<T>* tmp)
	{
		head = tmp;
	}
	lnode<T> * get_curr() const
	{
		return curr;
	}
	void set_curr(lnode<T> *tmp)
	{
		curr = tmp;
	}
	void delete_node(void)
	{
		if (curr == head)
		{
			lnode<T>* tmp = head;
			curr = head->get_next();
			head = curr;
			delete tmp;
			if(curr) curr->set_prev(0);
		}
		else
		{
			lnode<T>* tmp = curr;
			curr->get_prev()->set_next(curr->get_next());
			if(curr->get_next()) curr->get_next()->set_prev(curr->get_prev());
			curr = curr->get_next();
			delete tmp;
		}
		s = 1;
		
	}
	void add()
	{
		if (head)
		{
			lnode<T> *s = new lnode<T>;
			lnode<T> *tmp = curr->get_next();
			curr->set_next(s);
			s->set_next(tmp);
			curr = s;
		}
		else
		{
			lnode<T> *s = new lnode<T>;
			head = s;
			head->set_next(0);
			curr = head;
		}
	}
	///////////
	int checklike(const char * s, const char * check)
	{
		int i, j, k, l = strlen(check), ls = strlen(s);
		for (i = 0, j = 0; i < l && j < ls; i++, j++)
		{
			if (check[i] == '\\') {
				i++;
				if (check[i] != s[j]) return 0;
			}
			else if (check[i] != '_') 
			{
				if (check[i] != '%') 
				{
					if (check[i] != s[j]) return 0;
				}
				else {
					for (k = 0; k < ls - j + 1; k++) if (checklike(s + j + k, check + i + 1)) return 1;
					if (k == ls - j + 1) return 0;
				}
			}
		}
		if (j != ls) return 0;
		while (i < l && check + i)
		{
			if (check[i] != '%') return 0;
			i++;
		}
		return 1;
	}
	int check(lnode<T> *n, command* a, int f)
	{
		if (f ==1)
		{
			switch (a->get_c_name())
			{
			case EQ:
			{
				if (strcmp(a->get_name(), n->get_name()) == 0) return 1;
				break;
			}
			case NE:
			{
				if (strcmp(a->get_name(), n->get_name()) != 0) return 1;
				break;
			}
			case LT:
			{
				if (strcmp(a->get_name(), n->get_name()) > 0) return 1;
				break;
			}
			case GT:
			{
				if (strcmp(a->get_name(), n->get_name()) < 0) return 1;
				break;
			}
			case LE:
			{
				if (strcmp(a->get_name(), n->get_name()) >= 0) return 1;
				break;
			}
			case GE:
			{
				if (strcmp(a->get_name(), n->get_name()) <= 0) return 1;			
				break;
			}
			case LIKE:
			{
				if (checklike(n->get_name(), a->get_name())) return 1;
				break;
			}
			default:
				break;
			}
		}
		else if (f == 2)
		{
			switch (a->get_c_phone())
			{
			case EQ:
			{
				if (a->get_phone() == n->get_phone()) return 1;
				break;
			}
			case NE:
			{
				if (a->get_phone() != n->get_phone()) return 1;
				break;
			}
			case LT:
			{
				if (a->get_phone() > n->get_phone()) return 1;
				break;
			}
			case GT:
			{
				if (a->get_phone() < n->get_phone()) return 1;
				break;
			}
			case LE:
			{
				if (a->get_phone() >= n->get_phone()) return 1;
				break;
			}
			case GE:
			{
				if (a->get_phone() <= n->get_phone()) return 1;
				break;
			}
			default:
				break;
			}
		}
		else if (f == 3)
		{
			switch (a->get_c_group())
			{
			case EQ:
			{
				if (a->get_group() == n->get_group()) return 1;
				break;
			}
			case NE:
			{
				if (a->get_group() != n->get_group()) return 1;
				break;
			}
			case LT:
			{
				if (a->get_group() > n->get_group()) return 1;
				break;
			}
			case GT:
			{
				if (a->get_group() < n->get_group()) return 1;
				break;
			}
			case LE:
			{
				if (a->get_group() >= n->get_group()) return 1;
				break;
			}
			case GE:
			{
				if (a->get_group() <= n->get_group()) return 1;
				break;
			}
			default:
				break;
			}
		}
		return 0;
	}
	void do_spec_selectn(command *a, int fd)
	{
		int r = 0, l = 0;
		if(!curr) return;	
		if(!srchn.get_curr()) return;
		if ((a->get_oper()) == OP_NONE)
		{
			if (check(srchn.get_curr()->get_data(), a, 1)) 
			{
				srchn.get_curr()->get_data()->print(fd);
				if(a->get_c_name() == LT || a->get_c_name() == LE)
				{
					srchn.a_print(srchn.get_curr()->get_left(), fd);
					l = 1; r = 1;
				}
				if(a->get_c_name() == GT || a->get_c_name() == GE)
				{
					srchn.a_print(srchn.get_curr()->get_right(), fd);
					l = 1; r = 1;
				}
			}
		}
		else if (a->get_oper() == AND)
		{
			if (a->get_c_group() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 3) && check(srchn.get_curr()->get_data(), a, 1))
				{
					srchn.get_curr()->get_data()->print(fd);
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						l = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						r = 1;
					}
				}
			}
			if (a->get_c_phone() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 2) && check(srchn.get_curr()->get_data(), a, 1)) 
				{
					srchn.get_curr()->get_data()->print(fd);
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						l = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						r = 1;
					}
				}
			}
		}
		else if (a->get_oper() == OR)
		{
			if (a->get_c_group() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 3) || check(srchn.get_curr()->get_data(), a, 1)) 
				{
					srchn.get_curr()->get_data()->print(fd);
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						srchn.a_print(srchn.get_curr()->get_left(), fd);
						r = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						srchn.a_print(srchn.get_curr()->get_right(), fd);
						l = 1;
					}
				}
			}
			if (a->get_c_phone() &&  a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 2) || check(srchn.get_curr()->get_data(), a, 1)) 
				{
					srchn.get_curr()->get_data()->print(fd);
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						srchn.a_print(srchn.get_curr()->get_left(), fd);
						r = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						srchn.a_print(srchn.get_curr()->get_right(), fd);
						l = 1;
					}
				}
			}
		}
		avlnode<T>* tmp = srchn.get_curr();
		if(r && l) return;
		if (((strcmp(a->get_name(), tmp->get_data()->get_name()) <= 0) || a->get_c_name() == LIKE)  &&  tmp->get_left() && !r)
		{
			srchn.set_curr(tmp->get_left());
			do_spec_selectn(a, fd);
			srchn.set_curr(tmp);
		}	
		if (((strcmp(a->get_name(), tmp->get_data()->get_name()) >= 0) || a->get_c_name() == LIKE) && tmp->get_right() && !l)
		{
			srchn.set_curr(tmp->get_right());
			do_spec_selectn(a, fd);
			srchn.set_curr(tmp);
		}

	}	

	void do_spec_selectg(command *a, int fd)
	{
		int r = 0, l = 0;
		if ((a->get_oper()) == OP_NONE)
		{
			if (check(srchg.get_curr()->get_data(), a, 2)) 
			{
				srchg.get_curr()->get_data()->print(fd);
				if(a->get_c_phone() == LT || a->get_c_phone() == LE)
				{
					srchg.a_print(srchg.get_curr()->get_left(), fd);
					l = 1; r = 1;
				}
				if(a->get_c_phone() == GT || a->get_c_phone() == GE)
				{
					srchg.a_print(srchg.get_curr()->get_right(), fd);
					l = 1; r = 1;
				}
			}
		}
		else if (a->get_oper() == AND)
		{
			if (a->get_c_name() && a->get_c_phone())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) && check(srchg.get_curr()->get_data(), a, 1))
				{
					srchg.get_curr()->get_data()->print(fd);
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						l = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						r = 1;
					}
				}
			}
			if (a->get_c_phone() && a->get_c_group())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) && check(srchg.get_curr()->get_data(), a, 3)) 
				{
					srchg.get_curr()->get_data()->print(fd);
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						l = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						r = 1;
					}
				}
	
		}
		}
		else if (a->get_oper() == OR)
		{
			if (a->get_c_name() && a->get_c_phone())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) || check(srchg.get_curr()->get_data(), a, 1)) 
				{
					srchg.get_curr()->get_data()->print(fd);
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						srchg.a_print(srchg.get_curr()->get_left(), fd);
						r = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						srchg.a_print(srchg.get_curr()->get_right(), fd);
						l = 1;
					}
				}
			}
			if (a->get_c_phone() &&  a->get_c_group())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) || check(srchg.get_curr()->get_data(), a, 3)) 
				{
					srchg.get_curr()->get_data()->print(fd);
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						srchg.a_print(srchg.get_curr()->get_left(), fd);
						r = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						srchg.a_print(srchg.get_curr()->get_right(), fd);
						l = 1;
					}
				}
			}
		}
		avlnode<T>* tmp = srchg.get_curr();
		if(r && l) return;
		if ((a->get_phone() <= tmp->get_data()->get_phone()) && tmp->get_left() && !r)
		{
			srchg.set_curr(tmp->get_left());
			do_spec_selectg(a, fd);
			srchg.set_curr(tmp);
		}	
		if ((a->get_phone() >= tmp->get_data()->get_phone()) && tmp->get_right() && !l)
		{
			srchg.set_curr(tmp->get_right());
			do_spec_selectg(a, fd);
			srchg.set_curr(tmp);
		}

	}
	void do_spec_deleten(command *a, stack<lnode<T>*> * ms)
	{
		int r = 0, l = 0;
		if(!curr) return;
  	 	if ((a->get_oper()) == OP_NONE)
		{
			if (a->get_c_name()) if (check(srchn.get_curr()->get_data(), a, 1)) 
			{
				ms->push(srchn.get_curr()->get_data());
				if(a->get_c_name() == LT || a->get_c_name() == LE)
				{
					srchn.a_stack(srchn.get_curr()->get_left(), ms);
					l = 1; r = 1;
				}
				if(a->get_c_name() == GT || a->get_c_name() == GE)
				{
					srchn.a_stack(srchn.get_curr()->get_right(), ms);
					l = 1; r = 1;
				}
			}
		}
		else if (a->get_oper() == AND)
		{
			if (a->get_c_group() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 3) && check(srchn.get_curr()->get_data(), a, 1))
				{
					ms->push(srchn.get_curr()->get_data());
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						l = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						r = 1;
					}
				}
			}
			if (a->get_c_phone() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 2) && check(srchn.get_curr()->get_data(), a, 1)) 
				{
					ms->push(srchn.get_curr()->get_data());
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						l = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						r = 1;
					}
				}
			}
		}
		else if (a->get_oper() == OR)
		{
			if (a->get_c_group() && a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 3) || check(srchn.get_curr()->get_data(), a, 1)) 
				{
					ms->push(srchn.get_curr()->get_data());
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						srchn.a_stack(srchn.get_curr()->get_left(), ms);
						r = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						srchn.a_stack(srchn.get_curr()->get_right(), ms);
						l = 1;
					}
				}
			}
			if (a->get_c_phone() &&  a->get_c_name())
			{
				if (check(srchn.get_curr()->get_data(), a, 2) || check(srchn.get_curr()->get_data(), a, 1)) 
				{
					ms->push(srchn.get_curr()->get_data());
					if(a->get_c_name() == LT || a->get_c_name() == LE)
					{
						srchn.a_stack(srchn.get_curr()->get_left(), ms);
						r = 1;
					}
					if(a->get_c_name() == GT || a->get_c_name() == GE)
					{
						srchn.a_stack(srchn.get_curr()->get_right(), ms);
						l = 1;
					}
				}
			}
		}
		avlnode<T>* tmp = srchn.get_curr();
		if(r && l) return;
		if (((strcmp(a->get_name(), tmp->get_data()->get_name()) <= 0) || a->get_oper() == OR || a->get_c_name() == LIKE)  &&  tmp->get_left() && !r)
		{
			srchn.set_curr(tmp->get_left());
			do_spec_deleten(a, ms);
			srchn.set_curr(tmp);
		}	
		if (((strcmp(a->get_name(), tmp->get_data()->get_name()) >= 0) || a->get_oper() == OR || a->get_c_name() == LIKE)  &&  tmp->get_right() && !l)
		{
			srchn.set_curr(tmp->get_right());
			do_spec_deleten(a, ms);
			srchn.set_curr(tmp);
		}
	}

	void do_spec_deleteg(command *a, stack<lnode<T>*> * ms)
	{
		int r = 0, l = 0;
		if(!curr) return;
  	 	if ((a->get_oper()) == OP_NONE)
		{
			if (a->get_c_phone()) if (check(srchg.get_curr()->get_data(), a, 2)) 
			{
				ms->push(srchg.get_curr()->get_data());
				if(a->get_c_phone() == LT || a->get_c_phone() == LE)
				{
					srchg.a_stack(srchg.get_curr()->get_left(), ms);
					l = 1; r = 1;
				}
				if(a->get_c_phone() == GT || a->get_c_phone() == GE)
				{
					srchg.a_stack(srchg.get_curr()->get_right(), ms);
					l = 1; r = 1;
				}
			}
		}
		else if (a->get_oper() == AND)
		{
			if (a->get_c_phone() && a->get_c_name())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) && check(srchg.get_curr()->get_data(), a, 1))
				{
					ms->push(srchg.get_curr()->get_data());
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						l = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						r = 1;
					}
				}
			}
			if (a->get_c_phone() && a->get_c_group())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) && check(srchg.get_curr()->get_data(), a, 3)) 
				{
					ms->push(srchg.get_curr()->get_data());
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						l = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						r = 1;
					}
				}
			}
		}
		else if (a->get_oper() == OR)
		{
			if (a->get_c_phone() && a->get_c_name())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) || check(srchg.get_curr()->get_data(), a, 1)) 
				{
					ms->push(srchg.get_curr()->get_data());
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						srchg.a_stack(srchg.get_curr()->get_left(), ms);
						r = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						srchg.a_stack(srchg.get_curr()->get_right(), ms);
						l = 1;
					}
				}
			}
			if (a->get_c_phone() &&  a->get_c_group())
			{
				if (check(srchg.get_curr()->get_data(), a, 2) || check(srchg.get_curr()->get_data(), a, 3)) 
				{
					ms->push(srchg.get_curr()->get_data());
					if(a->get_c_phone() == LT || a->get_c_phone() == LE)
					{
						srchg.a_stack(srchg.get_curr()->get_left(), ms);
						r = 1;
					}
					if(a->get_c_phone() == GT || a->get_c_phone() == GE)
					{
						srchg.a_stack(srchg.get_curr()->get_right(), ms);
						l = 1;
					}
				}
			}
		}
		avlnode<T>* tmp = srchg.get_curr();
		if(r && l) return;
		if (((a->get_phone() <= tmp->get_data()->get_phone()) || a->get_oper() == OR) && tmp->get_left() && !r)
		{
			srchg.set_curr(tmp->get_left());
			do_spec_deleteg(a, ms);
			srchg.set_curr(tmp);
		}	
		if (((a->get_phone() >= tmp->get_data()->get_phone()) || a->get_oper() == OR) && tmp->get_right() && !l)
		{
			srchg.set_curr(tmp->get_right());
			do_spec_deleteg(a, ms);
			srchg.set_curr(tmp);
		}

	}
	void do_select(avlnode<T>*r, int fd)
	{
		if(r->get_left()) do_select(r->get_left(), fd);
		if(r->get_right()) do_select(r->get_right(), fd);
	
		r->get_data()->print(fd);
	}
	
	void do_delete(avlnode<T>*r, list<T>*sec)
	{
		
		if(r->get_right()) do_delete(r->get_right(), sec);	
		if(r->get_left()) do_delete(r->get_left(), sec);

		int i = 0, j = 0;
		sec->set_havln(sec->get_avln().get_head()->deln(r->get_data(), sec->get_avln().get_head(), &i, &j));
		i = 0;
		sec->set_havlg(sec->get_avlg().get_head()->delg(r->get_data(), sec->get_avlg().get_head(), &i));
		
		sec->set_curr(r->get_data());
		sec->delete_node();
		
		delete r;
		r = 0;
		
	}

	void do_insert(command *a, list<T>*sec, avl<list<T>>* ggg)
	{
		lnode<T>*tmp = new lnode<T>;
		avlnode<T> *n = new avlnode<T>;	
		tmp->init(a->get_name(), a->get_phone(), a->get_group());
		n->set_data(tmp);

		int i = 0;
		srch = -2;
		avlnode<T> *q = sec->get_avln().get_head()->addn(n, sec->get_avln().get_head(), &i);
		if(srch == 1) { delete tmp; delete n; srch = 0; return; }
		srch = 0;
		sec->set_havln(q);

		if(sec->get_head())
		{	
			tmp->set_next(sec->get_head());
			sec->get_head()->set_prev(tmp);
			tmp->set_prev(0);
			sec->set_head(tmp);
			sec->set_curr(head);
		}
		else
		{
			sec->set_head(tmp);
			sec->set_curr(tmp);
		}
		
		avlnode<T> *m = new avlnode<T>;	
		avlnode<T> *ng = new avlnode<T>;
		avlnode<T> *mg = new avlnode<T>;
		m->set_data(tmp);
		ng->set_data(tmp);
		mg->set_data(tmp);
		i = 0;
		sec->set_havlg(sec->get_avlg().get_head()->addg(m, sec->get_avlg().get_head(), &i));
		if(!ggg)
		{
			i = 0;
			srchg.set_head(srchg.get_head()->addg(mg, srchg.get_head(), &i));
			i = 0;	
			srchn.set_head(srchn.get_head()->addn(ng, srchn.get_head(), &i));
		}
		else	
		{
			avlnode<list<T>> * groot = new avlnode<list<T>>;
			lnode<list<T>> * gtmp = new lnode<list<T>>;
			
			gtmp->gr = a->get_group();
			gtmp->set_head(tmp);
			gtmp->set_curr(tmp);
			groot->set_data(gtmp);
			groot->set_left(0); groot->set_right(0);
			
			ng->set_left(0); ng->set_right(0); ng->set_balance(0);	
			mg->set_left(0); mg->set_right(0); mg->set_balance(0);
			int i = 0;
				
			ggg->set_head(ggg->get_head()->addn(groot, ggg->get_head(), &i));	
			gtmp->set_havln(ng);
			gtmp->set_cavln(ng);
			gtmp->set_havlg(mg);
			gtmp->set_cavlg(mg);
		}
	

			
	}
	
	void insavl(avlnode<list<T>>*f, avlnode<T>*c1, avlnode<T>*c2, int *w)
	{
		if(f->get_data()->get_avln().get_head()->get_data()->get_group() == c1->get_data()->get_group())
		{
			int i = 0;
			f->get_data()->set_havln(f->get_data()->get_avln().get_head()->addn(c1, f->get_data()->get_avln().get_head(), &i));
			i = 0;	
			f->get_data()->set_havlg(f->get_data()->get_avlg().get_head()->addg(c2, f->get_data()->get_avlg().get_head(), &i));
			*w = 1;
			return;
		}
		if(f->get_left() && !(*w))
		{
			insavl(f->get_left(), c1, c2, w);
		}
		if(f->get_right() && !(*w))
		{
			insavl(f->get_right(), c1, c2, w);
		}
	}

	void delavl(avlnode<list<T>>*f, lnode<T>*c, int *w, lnode<list<T>>** omg)
	{
		if(f->get_data()->gr == c->get_group())
		{
			int i = 0, j = 0;
			f->get_data()->set_havln(f->get_data()->get_avln().get_head()->deln(c, f->get_data()->get_avln().get_head(), &i, &j));
			i = 0;	
			f->get_data()->set_havlg(f->get_data()->get_avlg().get_head()->delg(c, f->get_data()->get_avlg().get_head(), &i));
			if(!f->get_data()->get_avln().get_head()) 
			{
				*omg = f->get_data();
			}
			*w = 1;
			return;
		}
		if(f->get_left() && !(*w))
		{
			delavl(f->get_left(), c, w, omg);
		}
		if(f->get_right() && !(*w))
		{
			delavl(f->get_right(), c, w, omg);
		}
	}
	void do_it(int fd, command *a, avlnode<list<T>>*first, list<T>*sec, avl<list<T>> *ggg, int *f = 0)
	{
	curr = head;
	if (a->get_c_name() != COND_NONE)
		{
			srchn.set_curr(srchn.get_head());
			if (a->get_type() == SELECT)
			{	
				do_spec_selectn(a, fd);
				return;
			}
			if (a->get_type() == DELETE)
			{
				stack<lnode<T>*> *ms = new stack<lnode<T>*>;
				do_spec_deleten(a, ms);
				while(!ms->empty())
				{
					curr = ms->top();	
					int i = 0, j = 0;
					srchn.set_head(srchn.get_head()->deln(curr, srchn.get_head(), &i, &j));
					i = 0;
					srchg.set_head(srchg.get_head()->delg(curr, srchg.get_head(), &i));
					if(!sec)
					{
						int w = 0, q = 0, zxc = 1;
						lnode<list<T>>* helpme = 0;
						delavl(first, curr, &w, &helpme);
						delete_node();
						if(helpme) ggg->set_head(ggg->get_head()->deln(helpme, ggg->get_head(), &q, &zxc));
					}			
					else 
					{ 
						int i = 0, j = 0;
						sec->set_havln(sec->get_avln().get_head()->deln(curr, sec->get_avln().get_head(), &i, &j));
						i = 0;
						sec->set_havlg(sec->get_avlg().get_head()->delg(curr, sec->get_avlg().get_head(), &i));

						sec->set_curr(curr); 
						sec->delete_node(); 
					}
				
					ms->pop();
					srchn.set_curr(srchn.get_head());
				}
				delete ms;
				return;
			}

		}
	
		
		else 
		{ 
			if(a->get_c_phone() != COND_NONE)
			{
				srchg.set_curr(srchg.get_head());
				if (a->get_type() == SELECT)
				{
					do_spec_selectg(a, fd);
					return;
				}
				if (a->get_type() == DELETE)
				{
					stack<lnode<T>*> *ms = new stack<lnode<T>*>;
					do_spec_deleteg(a, ms);
					while(!ms->empty())
					{
						int i = 0, j = 0;
						curr = ms->top();
						srchg.set_head(srchg.get_head()->delg(curr, srchg.get_head(), &i));
						i = 0;
						srchn.set_head(srchn.get_head()->deln(curr, srchn.get_head(), &i, &j));
						if(!sec)
						{
							int w = 0, q = 0, zxc = 1;
							lnode<list<T>>* helpme = 0;
							delavl(first, curr, &w, &helpme);
							delete_node();
							if(helpme) ggg->set_head(ggg->get_head()->deln(helpme, ggg->get_head(), &q, &zxc));
						}			
						else 
						{ 
							int i = 0, j = 0;
							sec->set_havln(sec->get_avln().get_head()->deln(curr, sec->get_avln().get_head(), &i, &j));
							i = 0;
							sec->set_havlg(sec->get_avlg().get_head()->delg(curr, sec->get_avlg().get_head(), &i));
	
							sec->set_curr(curr); 
							sec->delete_node(); 
						}	
									
						ms->pop();
						srchg.set_curr(srchg.get_head());
					}
					delete ms;
					return;
				}
			}
			 
			else
			{
				if (a->get_type() == SELECT)
				{
					do_select(srchn.get_head(), fd);
					return;
				}
				if (a->get_type() == DELETE)
				{
					*f = 2;	
					curr = head;
					do_delete(srchn.get_head(), sec);
			
					moredelete(srchg.get_head());
					return;
				}
			}
		}

		do_insert(a, sec, ggg);
	}
	
	void moredelete(avlnode<T>* r)
	{
		if(r->get_left()) moredelete(r->get_left());
		if(r->get_right()) moredelete(r->get_right());
		delete r;
	}


	////////supply
	
	void l_delete()
	{
		srchn.set_curr(srchn.get_head());
		srchn.a_delete();	
		srchg.set_curr(srchg.get_head());
		srchg.a_delete();
		curr = head;
		while (curr)
		{
			lnode<T> *tmp = curr->get_next();
			delete curr;
			curr = tmp;
		}
		head = 0;
		curr = 0;
	}
	void l_print(int fd)
	{
		int mp = MP;
		curr = head;
		lnode<T> *tmp = curr;
		while (mp && curr)
		{
			curr->print(fd);
			curr = curr->get_next();
			cout << endl;
			mp--;
		}
		curr = tmp;
	}
	int l_read(FILE *fp)
	{
		lnode<T> *root = new lnode<T>;
		if (!root) return -1;
		if (root->read(fp)) { delete root;  return -2; }
		head = root;
		head->set_prev(0);
		curr = head;
		while (1)
		{
			lnode<T> *tmp = new lnode<T>;
			if (!tmp)  return -3;
			if (tmp->read(fp)) { delete tmp;  break; }
			curr->set_next(tmp);
			tmp->set_prev(curr);
			curr = tmp;
		}
		curr->set_next(0);
		curr = head;

		srchn.a_readn(head);
		srchg.a_readg(head);
		return 0;
	}
};


#endif
