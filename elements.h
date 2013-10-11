#include <boost/optional.hpp>
#include <stdint.h>
#include <string>
#include <list>
#include <map>
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

struct Elem {
    DATA_TYPE type;
    std::string valStr;
    int valInt;
    double valDbl;
    std::vector<std::shared_ptr<Elem> > valList;

    Elem() : type(DATA_TYPE::NILL), valStr(""), valInt(0), valDbl(0.0)
            , valList() {
    }

    Elem(const Elem& other) : type(other.type), valStr(other.valStr), valInt(other.valInt)
            , valDbl(other.valDbl), valList(other.valList.begin(),other.valList.end()) {
    }

};

inline void makeSymb(std::shared_ptr<Elem> element, const std::string& val) {
    element->type = DATA_TYPE::SYMBOL;
    element->valStr = val;
}

inline void makeStr(std::shared_ptr<Elem> element, const std::string& val) {
    element->type = DATA_TYPE::STRING;
    element->valStr = val;
}

inline void makeDbl(std::shared_ptr<Elem> element, const double val) {
    element->type = DATA_TYPE::DOUBLE;
    element->valDbl = val;
}

inline void makeInt(std::shared_ptr<Elem> element, const int val) {
    element->type = DATA_TYPE::INT;
    element->valInt = val;
}

inline void makeQuote(std::shared_ptr<Elem> element, const std::string& varName, Elem* valueElement) {
    element->valStr = "QUOTE";
    element->type = DATA_TYPE::QUOTE;
    Elem *varElement = new Elem();
    varElement->valStr = "variable";
    varElement->type = DATA_TYPE::SYMBOL;
    varElement->valList.push_back(std::shared_ptr<Elem>(valueElement));
    element->valList.push_back(std::shared_ptr<Elem>(varElement));
}

struct Env {
    typedef std::map<std::string,std::shared_ptr<Elem> > ENV_VAR_TYPE;
    ENV_VAR_TYPE d_vars;
    Env* d_outer;

    Env(Env* outer) : d_outer(outer) {
    }

    std::shared_ptr<Elem> operator[](const std::string& key) {
        auto it = d_vars.find(key);
        if (it == d_vars.end()) {
            return nullptr;
        } else {
            return it->second;
        }
    }

    void insert(const std::string& key, std::shared_ptr<Elem> value) {
        d_vars[key] = value;
    }

    Env* findInHier(const std::string& key) {
        if (this->operator[](key) != nullptr) {
            return const_cast<Env*>(this);
        } else if (d_outer != nullptr) {
            return d_outer->findInHier(key);
        } else {
            return nullptr;
        }
    }
};
