#include "parser.h"
#include "boost/lexical_cast.hpp"

boost::sregex_token_iterator Parser::Tokenize() {
    const boost::regex  leftParen("(\\()");
    const boost::regex rightParen("(\\))");
    const std::string leftReplace(" \\1 ");
    const std::string rightReplace(" \\1 ");

    std::string leftRes = regex_replace(d_line, leftParen, leftReplace, boost::match_default | boost::format_sed);
    d_line = regex_replace(leftRes, rightParen, rightReplace, boost::match_default | boost::format_sed);
    return boost::sregex_token_iterator(d_line.begin(), d_line.end(), boost::regex("\\s+"), -1);
};



elemSet Parser::readFromTokens(
        boost::sregex_token_iterator& beginIt, 
        boost::sregex_token_iterator endIt) {
    if (beginIt == endIt) {
        throw std::runtime_error("unexpected EOF while reading");
    } else if (beginIt->str() == "(") {
        elemSet retVal; 
        std::shared_ptr<Elem> procElem(new Elem());
        beginIt++;
        while ((beginIt != endIt) && (beginIt->str() != ")")) {
            auto parsedVal = readFromTokens(beginIt,endIt);
            if (parsedVal.size() != 1) {
                std::shared_ptr<Elem> expRetVal(new Elem());
                expRetVal->valExp = parsedVal;
                retVal.push_back(expRetVal);
            } else {
                retVal.push_back(parsedVal[0]);
            }
            if (beginIt == endIt) {
                throw std::runtime_error("unexpected EOF while reading");
            }
            beginIt++;
        }
        if (beginIt != endIt) {
            beginIt++;
        }
        procElem->valExp = retVal;
        procElem->type = DATA_TYPE::PROC;
        elemSet procVal = { procElem };
        return procVal;
    } else {
        elemSet retVal;
        std::shared_ptr<Elem> expRetVal(new Elem());
        try {
            int intVal = boost::lexical_cast<int>(*beginIt);
            expRetVal->valInt = intVal;
            expRetVal->type = DATA_TYPE::INT;
        } catch (boost::bad_lexical_cast &) {
            try {
                double doubleVal = boost::lexical_cast<double>(*beginIt);
                expRetVal->valDbl = doubleVal;
                expRetVal->type = DATA_TYPE::DOUBLE;
            } catch (boost::bad_lexical_cast&) {
                expRetVal->valStr = (*beginIt);
                expRetVal->type = DATA_TYPE::STRING;
            }
        }
        retVal.push_back(expRetVal);
        return retVal;
    }
}

