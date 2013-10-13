#include <parser.h>

boost::sregex_token_iterator Parser::Tokenize(std::string& result) {
    const boost::regex  leftParen("(\\()");
    const boost::regex rightParen("(\\))");
    const std::string leftReplace(" \\1 ");
    const std::string rightReplace(" \\1 ");

    std::string leftRes = regex_replace(d_line, leftParen, leftReplace, boost::match_default | boost::format_sed);
    result = regex_replace(leftRes, rightParen, rightReplace, boost::match_default | boost::format_sed);
    return boost::sregex_token_iterator(result.begin(), result.end(), boost::regex("\\s+"), -1);
};
