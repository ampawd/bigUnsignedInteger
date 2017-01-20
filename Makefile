CC=g++

CFLAGS=-c -Wall -std=c++11

PROG=buint

OBJS=main.o big_uint.o


all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(OBJS) -o $(PROG)

main.o:
	$(CC) $(CFLAGS) main.cpp

big_uint.o:
	$(CC) $(CFLAGS) big_uint.cpp

clean:
	rm -rf *.o *.gch $(PROG)
