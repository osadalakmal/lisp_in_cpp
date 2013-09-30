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
    ENV_VAR_TYPE vars;
    std::shared_ptr<Elem*> operator[](const std::string& key) {
        ENV_VAR_TYPE::iterator it = vars.find(key);
        if (it == vars.end()) {
            return NULL;
        } else {
            return it->second;
        }
    }
};
