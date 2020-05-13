#include "student.h"

template <class T>
class QNode : public T
{
private:
	QNode * next;

public:
	QNode(const char * n = 0, int v = 0) : T(n, v) { next = 0; }
	QNode(const QNode& i) : T(i) { next = 0; }
	~QNode() { next = 0; }
	QNode& operator=(const QNode& rhs) {
		*((T *)this) = rhs;
		next = 0;
		return *this;
	}
/*
	void operator==(const QNode& rhs) {
		this->name = rhs.name;
		this->value = rhs.value;
		next = 0;
	}
*/

	QNode * get_next() const { return next; }
	void set_next(QNode * n) { next = n; }
};

