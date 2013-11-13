#include <iostream>
#include "gtest/gtest.h"
#include "execinfo.h"
#include "signal.h"
#include "stdlib.h"

void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char* argv[])
{
    signal(SIGSEGV,handler);
    if (argc > 1 && strncmp(argv[1],"--test",strlen("--test")) == 0) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
    }
}
