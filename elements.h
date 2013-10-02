#include <stdint.h>
#include <string>
#include <map>
#include <memory>

enum DATA_TYPE {
    NILL,
    LIST,
    INT,
    DOUBLE,
    STRING,
    SYMBOL,
    IF
};

struct Elem {
    DATA_TYPE type;
    uint32_t size;
    void* data;
};

struct Env {
    typedef std::map<std::string,std::shared_ptr<Elem*> > ENV_VAR_TYPE;
    ENV_VAR_TYPE d_vars;
    Env* d_outer;

    Env(Env* outer) : d_outer(outer) {
    }

    std::shared_ptr<Elem*> operator[](const std::string& key) {
        ENV_VAR_TYPE::iterator it = d_vars.find(key);
        if (it == d_vars.end()) {
            return nullptr;
        } else {
            return it->second;
        }
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
