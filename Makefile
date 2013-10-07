
SRCS = main.cpp elements.cpp evaluator.cpp evaluator.t.cpp
HEADERS = evaluator.h elements.h
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = --std=c++0x -g -O3 -I. -I/home/osada/progs/projects/boost/boost_1_54_0/
CC = clang++

all: liscpp.tsk

$(OBJS): %.o : $(HEADERS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $<
#StringBuilder.t.o : StringBuilder.h

gtest-all.o : /usr/src/gtest/src/gtest-all.cc
	$(CC) -c /usr/src/gtest/src/gtest-all.cc -I/usr/src/gtest/

liscpp.tsk: $(OBJS) gtest-all.o
	$(CC) $(OBJS) gtest-all.o -o liscpp.tsk -lpthread -fno-line

.PHONY: clean

clean:
	rm -f gtest-all.o $(OBJS) liscpp.tsk

tests: liscpp.tsk
	./liscpp.tsk --test


