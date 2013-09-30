OBJS = main.o evaluator.o evaluator.t.o
CXXFLAGS = --std=c++0x -g -O6 -I.
CC = clang++

main.o : evaluator.o evaluator.t.o

#StringBuilder.t.o : StringBuilder.h

GTEST :
	g++ -c /usr/src/gtest/src/gtest-all.cc -I/usr/src/gtest/

build : main.o GTEST
	g++ $(OBJS) gtest-all.o -o liscpp.tsk -lpthread

.PHONY: clean

clean:
	rm -f gtest-all.o $(OBJS) liscpp.tsk

tests: build
	./liscpp.tsk --test


