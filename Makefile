CXX=g++

CXXFLAGS=-c -Wall -std=c++11

PROGNAME=buint

OBJS=main.o big_uint.o


all: $(PROGNAME)

$(PROGNAME): $(OBJS)
	$(CXX) $(OBJS) -o $(PROGNAME)

main.o:
	$(CXX) $(CXXFLAGS) main.cpp

big_uint.o:
	$(CXX) $(CXXFLAGS) big_uint.cpp

clean:
	rm -rf *.o *.gch $(PROGNAME)
