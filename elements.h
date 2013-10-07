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
    boost::optional<std::list<Elem> > valList;
};

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

    void insert(const std::string& key, Elem value) {
        d_vars[key] = std::shared_ptr<Elem>(new Elem(value));
    }

    Env* findInHier(const std::string& key) {
        if (this->operator[](key) == nullptr) {
            return const_cast<Env*>(this);
        } else if (d_outer != nullptr) {
            return d_outer->findInHier(key);
        } else {
            return nullptr;
        }
    }
};
