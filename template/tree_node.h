#include "stack.h"

template <class T, template <class> class T1,
template <class, template <class> class> class T2>
class TNode : public T2 <T, T1> {
private:
	TNode * level, * down;
public:
	TNode() { level = down = 0; }
	~TNode() { level = down = 0; }

	TNode * get_level() const { return level; }
	TNode * get_down() const { return down; }
	void set_level(TNode * l) { level = l; }
	void set_down(TNode * d) { down = d; }
};

