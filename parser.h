#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <elements.h>
#include <vector>

class Parser {
    std::string d_line;
public:
    Parser(std::string line) : d_line(line){}
    void parse(); 
    void readFromTokens();
    boost::sregex_token_iterator Tokenize(std::string& result);
    void convertToAtom();
};
