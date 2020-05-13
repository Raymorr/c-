#!/bin/bash
if [ "x$1" = x ]; then
	./a
else
	if [ "x$2" = x ]; then
		LeakCheck ./a $1 1 a.txt
	else
		LeakCheck ./a $1 $2 a.txt
	fi
	echo -----------------------------------
	cat leak.out
fi
#rm leak.out
