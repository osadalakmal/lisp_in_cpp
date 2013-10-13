#include <parser.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(Parser,Tokenize) {
    Parser parser("Hello World");
    std::string result;
    boost::sregex_token_iterator it = parser.Tokenize(result);
    boost::sregex_token_iterator j;
}
