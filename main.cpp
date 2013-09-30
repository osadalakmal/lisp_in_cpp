#include "gtest/gtest.h"

int main(int argc, char* argv[])
{
    if (argc > 1 && strncmp(argv[1],"--test",strlen("--test")) == 0) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
    }
}
