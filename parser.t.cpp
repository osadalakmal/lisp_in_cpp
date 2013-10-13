#include <parser.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(Parser,Tokenize) {
    Parser parser("(define operateTwice(lambda(op1 op2)(lambda(x y) (op2 (op1 x y) y))))");
    std::string result;
    boost::sregex_token_iterator it = parser.Tokenize(result);
    boost::sregex_token_iterator j;

    while(it != j)
    {
        std::cout << *it++ << std::endl;
    }
}
