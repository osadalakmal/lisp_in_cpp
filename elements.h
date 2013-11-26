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

typedef std::shared_ptr<Elem> ElemPtr;
typedef std::vector<ElemPtr> ElementSet;

inline void makeSymb(ElemPtr& element, const std::string& val) {
    element->type = DATA_TYPE::SYMBOL;
    element->valStr = val;
}

inline void makeValue(ElemPtr& element, const std::string& val) {
    element->type = DATA_TYPE::STRING;
    element->valStr = val;
}

inline void makeValue(ElemPtr& element, const double val) {
    element->type = DATA_TYPE::DOUBLE;
    element->valDbl = val;
}

inline void makeValue(ElemPtr& element, const int val) {
    element->type = DATA_TYPE::INT;
    element->valInt = val;
}

template <typename T>
inline ElemPtr makeSetCmd(const std::string& name, const T& value) {
	ElemPtr elem = std::make_shared<Elem>();
	ElemPtr varElem = std::make_shared<Elem>();
	ElemPtr valElem = std::make_shared<Elem>();
	elem->type = DATA_TYPE::SET;
	makeSymb(varElem,name);
	makeValue(valElem,value);
	elem->valExp.push_back(varElem);
	elem->valExp.push_back(valElem);
	return elem;
}

inline ElemPtr makeVar(const std::string& name) {
	ElemPtr varElem = std::make_shared<Elem>();
	makeSymb(varElem, name);
	return varElem;
}

typedef std::map<std::string,ElemPtr > ENV_VAR_TYPE;

struct Env {
    ENV_VAR_TYPE d_vars;
    Env* d_outer;

    Env(Env* outer) : d_vars(), d_outer(outer) {
        d_vars["global"] = std::make_shared<Elem>();
        d_vars["global"]->type = INT;
        d_vars["global"]->valInt = 11;
    }

    void insert(const std::string& key, ElemPtr& value) {
        d_vars.insert(std::make_pair(key, value));
    }

    ENV_VAR_TYPE& getMap() { return d_vars; }

    ElemPtr find(const std::string& key) {
        if (d_vars.find(key) != d_vars.end()) {
            return (d_vars.find(key))->second;
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

std::ostream& operator<<(std::ostream& out, ElemPtr elem);

#endif //INCLUDED_ELEMENTS_H
