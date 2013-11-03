
SRCS = main.cpp elements.cpp evaluator.cpp parser.cpp evaluator.t.cpp parser.t.cpp
HEADERS = evaluator.h elements.h parser.h
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = --std=c++0x -g -O0 -I. -I/usr/local/include/
CC = clang++

all: liscpp.tsk

$(OBJS): %.o : $(HEADERS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $<
#StringBuilder.t.o : StringBuilder.h

gtest-all.o : /usr/src/gtest/src/gtest-all.cc
	$(CC) -c /usr/src/gtest/src/gtest-all.cc -I/usr/src/gtest/

liscpp.tsk: $(OBJS) gtest-all.o
	$(CC) $(OBJS) gtest-all.o -o liscpp.tsk -Wl,-rpath,/usr/local/lib/ -lpthread -fno-line -L/usr/local/lib -lboost_regex

.PHONY: clean

clean:
	rm -f gtest-all.o $(OBJS) liscpp.tsk

tests: liscpp.tsk
	./liscpp.tsk --test


