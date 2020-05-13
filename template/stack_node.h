#include "queue.h"

template <class T, template <class> class T1>
class SNode : public T1 <T>
{
private:
	SNode * next;

public:
	SNode() { next = 0; }
	~SNode() { next = 0; }
	
	SNode * get_next() const { return next; }
	void set_next(SNode * n) { next = n; }
};

