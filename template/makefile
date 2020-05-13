F = -g -c -O3
all: a clean
clean:
	rm -f *.o
a: student.o main.o
	g++ student.o main.o -o a
student.o: student.cpp student.h
	g++ $F student.cpp
main.o: main.cpp tree.h tree_node.h stack.h stack_node.h queue.h queue_node.h student.h
	g++ $F main.cpp

