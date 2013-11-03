#ifndef INCLUDED_PARSER_H
#define INCLUDED_PARSER_H

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <elements.h>
#include <memory>
#include <vector>

class Parser {
    std::string d_line;
public:
    Parser(std::string line) : d_line(line){}
    elemSet parse(std::string& expr); 
    elemSet readFromTokens(
        boost::sregex_token_iterator& beginIt, 
        boost::sregex_token_iterator endIt);
    boost::sregex_token_iterator Tokenize();
    void convertToAtom();
};

#endif //INCLUDED_PARSER_H
