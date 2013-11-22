#include "parser.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Parser,Tokenize) {
    Parser parser("(define operateTwice(lambda(op1 op2)(lambda(x y) (op2 (op1 x y) y))))");
    boost::sregex_token_iterator it = parser.Tokenize();
    boost::sregex_token_iterator j;
    it++;
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"define");
    ASSERT_STREQ((it++)->str().c_str(),"operateTwice");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"lambda");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"op1");
    ASSERT_STREQ((it++)->str().c_str(),"op2");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"lambda");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"x");
    ASSERT_STREQ((it++)->str().c_str(),"y");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"op2");
    ASSERT_STREQ((it++)->str().c_str(),"(");
    ASSERT_STREQ((it++)->str().c_str(),"op1");
    ASSERT_STREQ((it++)->str().c_str(),"x");
    ASSERT_STREQ((it++)->str().c_str(),"y");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),"y");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),")");
    ASSERT_STREQ((it++)->str().c_str(),")");
}


TEST(Parser,ReadFromBasic) {
    Parser parser("(+ 5 5)");
    boost::sregex_token_iterator it = parser.Tokenize();
    boost::sregex_token_iterator j;
    it++;
    ElementSet result;
    ASSERT_NO_THROW(result = parser.readFromTokens(it,j));
    ASSERT_EQ(result.size(),1);
    ASSERT_EQ(result[0]->type,DATA_TYPE::PROC);
    ASSERT_EQ(result[0]->valExp.size(), 3);
    result = result[0]->valExp;
    ASSERT_STREQ(result[0]->valStr.c_str(),"+");
    ASSERT_EQ(result[1]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[1]->valInt,5);
    ASSERT_EQ(result[2]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[2]->valInt,5);
}


TEST(Parser,ReadFromInt1) {
    Parser parser("(* 2 (+ 5 5))");
    boost::sregex_token_iterator it = parser.Tokenize();
    boost::sregex_token_iterator j;
    it++;
    ElementSet result;
    ASSERT_NO_THROW(result = parser.readFromTokens(it,j));
    ASSERT_EQ(result.size(),1);
    ASSERT_EQ(result[0]->type,DATA_TYPE::PROC);
    ASSERT_EQ(result[0]->valExp.size(), 3);
    result = result[0]->valExp;
    ASSERT_STREQ(result[0]->valStr.c_str(),"*");
    ASSERT_EQ(result[1]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[1]->valInt,2);
    ASSERT_EQ(result[2]->type,DATA_TYPE::PROC);
    ASSERT_EQ(result[2]->valExp.size(), 3);
    result = result[2]->valExp;
    ASSERT_STREQ(result[0]->valStr.c_str(),"+");
    ASSERT_EQ(result[1]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[1]->valInt,5);
    ASSERT_EQ(result[2]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[2]->valInt,5);
}

TEST(Parser,ReadFromInt2) {
    Parser parser("(quote ((1) (2)))");
    boost::sregex_token_iterator it = parser.Tokenize();
    boost::sregex_token_iterator j;
    it++;
    ElementSet result;
    ASSERT_NO_THROW(result = parser.readFromTokens(it,j));
    ASSERT_EQ(result.size(),1);
    ASSERT_EQ(result[0]->type,DATA_TYPE::PROC);
    result = result[0]->valExp;
    ASSERT_EQ(result[0]->type,DATA_TYPE::QUOTE);
    ASSERT_EQ(result[1]->type,DATA_TYPE::PROC);
    result = result[1]->valExp;
    ASSERT_EQ(result[0]->type,DATA_TYPE::PROC);
    ASSERT_EQ(result[1]->type,DATA_TYPE::PROC);
    ASSERT_EQ(result[0]->valExp[0]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[0]->valExp[0]->valInt,1);
    ASSERT_EQ(result[1]->valExp[0]->type,DATA_TYPE::INT);
    ASSERT_EQ(result[1]->valExp[0]->valInt,2);

}
