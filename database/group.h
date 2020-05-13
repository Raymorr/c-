#ifndef qwe
#define qwe
#include "list.h"

template <class T>
class gr
{
private:
	list<T> base;
	avl<list<T>> grbase;
public:
	gr(){}
	~gr()
	{
		base.l_delete();
		grbase.set_curr(grbase.get_head());
		gr_delete();
	}
	void just_do_it(command* a, int fd)
	{
		int w = 0;
		if((a->get_c_group() == COND_NONE && a->get_type() != INSERT) || a->get_oper() == OR)
		{
			if(a->get_type() == DELETE) base.do_it(fd, a, grbase.get_head(), 0, &grbase);
			else base.do_it(fd, a, grbase.get_head(), 0, 0);
		}
		else do_it(fd, grbase.get_head(), a, &w);
		if(!w && a->get_type() == INSERT)
		{
			grbase.get_head()->get_data()->do_it(fd, a, 0, &base, &grbase);
		}
	}
	
	
	
	
	void do_it(int fd, avlnode<list<T>> *h, command*a, int *w)
	{
		if(h->get_data()->get_avln().get_head()->get_data()->get_group() == a->get_group()) 
		{
			int f = 1;
			h->get_data()->do_it(fd, a, 0, &base, 0, &f);
			*w = f;
			if(*w == 2)
			{
				int q = 0, zxc = 1;
				grbase.set_head(grbase.get_head()->deln(h->get_data(), grbase.get_head(), &q, &zxc, 0));
			}
			return;
		}
		if((a->get_group() > h->get_data()->gr) && h->get_left() && !(*w))
		{
			do_it(fd, h->get_left(), a, w);
		}
		if((a->get_group() < h->get_data()->gr) && h->get_right() && !(*w))
		{
			do_it(fd, h->get_right(), a, w);
		}
		

	}

	int gr_read(FILE *fp)
	{
		lnode<T> *root = new lnode<T>;
		avlnode<list<T>> * groot = new avlnode <list<T>>;
		
		if (!root) return -1;
		if (root->read(fp)) { delete root; return -2; }
		base.set_head(root);
		base.get_head()->set_prev(0);
		base.set_curr(base.get_head());
		base.get_curr()->set_next(0);

		lnode<list<T>> * tmp = new lnode<list<T>>;
		tmp->gr = root->get_group();
		groot->set_data(tmp);
		groot->set_left(0);
		groot->set_right(0);
		grbase.set_head(groot);
		grbase.set_curr(groot);
		//for list
		avlnode<T> *root1 = new avlnode<T>;
		if(!root1) { return -1; }
		avlnode<T> *root2 = new avlnode<T>;
		if(!root2) { delete root1; return -1; }
		root1->set_data(root);
		root2->set_data(root);
		root1->set_left(0);
		root1->set_right(0);
		root1->set_balance(0);
		root2->set_left(0);
		root2->set_right(0);
		root2->set_balance(0);
		//
		base.set_havln(root1);
		base.set_cavln(base.get_avln().get_head());
		base.set_havlg(root2);
		base.set_cavlg(base.get_avlg().get_head());
	
	
		//for grlist#1
	
		avlnode<T> *groot1 = new avlnode<T>;
		if(!groot1) { return -1; }
		avlnode<T> *groot2 = new avlnode<T>;
		if(!groot2) { delete root1; return -1; }
		groot1->set_data(root);
		groot2->set_data(root);
		groot1->set_left(0);
		groot1->set_right(0);
		groot1->set_balance(0);
		groot2->set_left(0);
		groot2->set_right(0);
		groot2->set_balance(0);
		//
		tmp->set_havln(groot1);
		tmp->set_cavln(groot->get_data()->get_avln().get_head());
		tmp->set_havlg(groot2);
		tmp->set_cavlg(groot->get_data()->get_avlg().get_head());
	
		while(1)
		{
			lnode<T>* d = new lnode<T>;
			if(!d) return -3;
			if(d->read(fp)) { delete d; break; }
			
			base.get_curr()->set_next(d);
			d->set_prev(base.get_curr());
			base.set_curr(d);
			//
			avlnode<T> *root1 = new avlnode<T>;
			if(!root1) { return -1; }
			avlnode<T> *root2 = new avlnode<T>;
			if(!root2) { delete root1; return -1; }
			
			root1->set_data(d);
			root2->set_data(d);
			int i = 0;
			base.set_havln(base.get_avln().get_head()->addn(root1, base.get_avln().get_head(), &i));
			i = 0;
			base.set_havlg(base.get_avlg().get_head()->addg(root2, base.get_avlg().get_head(), &i));
		
			avlnode<T> *groot1 = new avlnode<T>;
			if(!groot1) { return -1; }
			avlnode<T> *groot2 = new avlnode<T>;
			if(!groot2) { delete groot1; return -1; }
			groot1->set_data(d);
			groot2->set_data(d);
			groot1->set_left(0);
			groot1->set_right(0);
			groot1->set_balance(0);
			groot2->set_left(0);
			groot2->set_right(0);
			groot2->set_balance(0);		
			//
			
			int f = 0;	
			gr_search(grbase.get_head(), d, &f, groot1, groot2);
			if(!f)
			{
				avlnode<list<T>> *groot = new avlnode<list<T>>;
				lnode<list<T>> * tmp = new lnode<list<T>>;
				
				tmp->gr = d->get_group();	
				if (!tmp) return -3;
				tmp->set_head(d);
				tmp->set_curr(tmp->get_head());	

				groot->set_data(tmp);
				groot->set_left(0);
				groot->set_right(0);
				int i = 0;
				grbase.set_head(grbase.get_head()->addn(groot, grbase.get_head(), &i));
			
				tmp->set_havln(groot1);
				tmp->set_cavln(groot->get_data()->get_avln().get_head());
				tmp->set_havlg(groot2);
				tmp->set_cavlg(groot->get_data()->get_avlg().get_head());
				
		
			}
			
		}
		
		base.get_curr()->set_next(0);
		base.set_curr(base.get_head());
		return 0;
	}	

	void gr_search(avlnode<list<T>>* root, lnode<T> *d, int *f, avlnode<T>*r1, avlnode<T>*r2)
	{
		if(!root) return;
		int cmp = root->get_data()->gr - d->get_group();
		if(!cmp)
		{
			*f = 1;
			int i = 0;
			root->get_data()->set_havln(root->get_data()->get_avln().get_head()->addn(r1, root->get_data()->get_avln().get_head(), &i));
			i = 0;
			root->get_data()->set_havlg(root->get_data()->get_avlg().get_head()->addg(r2, root->get_data()->get_avlg().get_head(), &i));
			return;
		}
		else if(cmp < 0 && root->get_left() && !(*f))
		{
			gr_search(root->get_left(), d, f, r1, r2);
		}
		else if(cmp > 0 && root->get_right() && !(*f))
		{
			gr_search(root->get_right(), d, f, r1, r2);
		}
	}

	list<T>* get_list(void)
	{
		return &base;
	}
	avlnode<list<T>>* get_head(void)
	{
		return grbase.get_head();
	}
	avl<list<T>>* get_ggg(void)
	{
		return &grbase;
	}
	void gr_delete(void)
	{
		avlnode<list<T>> *tmp = grbase.get_curr();
		
		if (grbase.get_curr()->get_left())
		{
			grbase.set_curr(grbase.get_curr()->get_left());
			gr_delete();
			grbase.set_curr(tmp);
		}
		
		if (grbase.get_curr()->get_right())
		{
			grbase.set_curr(grbase.get_curr()->get_right());
			gr_delete();
			grbase.set_curr(tmp);
		
		}
		tmp->get_data()->set_cavln(tmp->get_data()->get_avln().get_head());
		tmp->get_data()->get_avln().a_delete();
		tmp->get_data()->set_cavlg(tmp->get_data()->get_avlg().get_head());
		tmp->get_data()->get_avlg().a_delete();
		delete tmp->get_data();
		delete tmp;
		tmp = 0;
	}
};
#endif
