SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CFLAGS= -Wall -I.. -fPIC
LDFLAGS=
NAME=example

all: $(OBJS)
	gcc -shared -o p1.so player1.o
	gcc -shared -o p2.so player2.o
	gcc -shared -o p3.so player3.o
	gcc -shared -o p4.so player4.o
	gcc -shared -o p5.so player5.o
	gcc -shared -o p6.so player6.o
	gcc -shared -o p7.so player7.o
	gcc -shared -o p8.so player8.o

clean:
	rm $(OBJS)
	rm *.so
