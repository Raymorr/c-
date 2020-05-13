F = -std=c++11 -O3
all: client server

client: client.cpp makefile
	g++ $F client.cpp -o client

server: main.cpp comand.cpp *.h makefile
	g++ $F main.cpp comand.cpp -o server

clear:
	rm *.o server client

