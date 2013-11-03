#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <elements.h>
#include <memory>
#include <vector>

class Parser {
    std::string d_line;
public:
    Parser(std::string line) : d_line(line){}
    void parse(); 
    elemSet readFromTokens(
        boost::sregex_token_iterator& beginIt, 
        boost::sregex_token_iterator endIt);
    boost::sregex_token_iterator Tokenize();
    void convertToAtom();
};
