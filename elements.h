#ifndef INCLUDED_ELEMENTS_H
#define INCLUDED_ELEMENTS_H

#include <boost/optional.hpp>
#include <stdint.h>
#include <string>
#include <list>
#include <map>
#include <stdexcept>
#include <memory>

enum DATA_TYPE {
    NILL = 0,
    LIST,
    INT,
    DOUBLE,
    STRING,
    SYMBOL,
    IF,
    DEFINE,
    SET,
    QUOTE,
    LAMBDA,
    BEGIN,
    PROC
};

inline std::string convertToStr(DATA_TYPE opType) {
        switch (opType) {
            case NILL:
                return "NILL";
            case LIST:
                return "LIST";
            case INT:
                return "INT";
            case DOUBLE:
                return "DOUBLE";
            case STRING:
                return "STRING";
            case SYMBOL:
                return "SYMBOL";
            case IF:
                return "IF";
            case DEFINE:
                return "DEFINE";
            case SET:
                return "SET";
            case QUOTE:
                return "QUOTE";
            case LAMBDA:
                return "LAMBDA";
            case BEGIN:
                return "BEGIN";
            case PROC:
                return "PROC";
            default:
                throw std::runtime_error("unknown op type");
        }
}

struct Elem {
    DATA_TYPE type;
    std::string valStr;
    int valInt;
    double valDbl;
    std::vector<std::shared_ptr<Elem> > valExp;

    Elem() : type(DATA_TYPE::NILL), valStr(""), valInt(0), valDbl(0.0)
            , valExp() {
    }

    Elem(const Elem& other) : type(other.type), valStr(other.valStr), valInt(other.valInt)
            , valDbl(other.valDbl), valExp(other.valExp) {
    }

    virtual ~Elem() {
    }

};

typedef std::vector<std::shared_ptr<Elem> > elemSet;

inline void makeSymb(std::shared_ptr<Elem>& element, const std::string& val) {
    element->type = DATA_TYPE::SYMBOL;
    element->valStr = val;
}

inline void makeStr(std::shared_ptr<Elem>& element, const std::string& val) {
    element->type = DATA_TYPE::STRING;
    element->valStr = val;
}

inline void makeDbl(std::shared_ptr<Elem>& element, const double val) {
    element->type = DATA_TYPE::DOUBLE;
    element->valDbl = val;
}

inline void makeInt(std::shared_ptr<Elem>& element, const int val) {
    element->type = DATA_TYPE::INT;
    element->valInt = val;
}

inline void makeOP(DATA_TYPE opType, std::shared_ptr<Elem>& element, std::shared_ptr<Elem> expElement) {
    element->valStr = convertToStr(opType);
    element->type = opType;
    element->valExp.push_back(expElement);
}

struct Env {
    typedef std::map<std::string,std::shared_ptr<Elem> > ENV_VAR_TYPE;
    ENV_VAR_TYPE d_vars;
    Env* d_outer;

    Env(Env* outer) : d_outer(outer),d_vars() {
        d_vars["global"] = std::make_shared<Elem>();
        d_vars["global"]->type = INT;
        d_vars["global"]->valInt = 11;
    }

    void insert(const std::string& key, std::shared_ptr<Elem>& value) {
        d_vars.insert(std::make_pair(key,std::shared_ptr<Elem>( new Elem())));
    }

    std::shared_ptr<Elem> find(const std::string& key) {
        if (this->d_vars.find(key) != this->d_vars.end()) {
            return (this->d_vars.find(key))->second;
        } else {
            return nullptr;
        }
    }

    Env* findInHier(const std::string& key) {
        if (this->d_vars.find(key) != this->d_vars.end()) {
            return const_cast<Env*>(this);
        } else if (d_outer != nullptr) {
            return d_outer->findInHier(key);
        } else {
            return nullptr;
        }
    }
};

std::ostream& operator<<(std::ostream& out, std::shared_ptr<Elem> elem);

#endif //INCLUDED_ELEMENTS_H
