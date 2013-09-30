#include <evaluator.h>
#include <cassert>

DATA_TYPE Evaluator::eval(std::list<Elem*>& elements, Env* env, void*& outVal) {
    assert(env);
    DATA_TYPE retType;
    if (!elements.size()) {
        return NILL;
    } else if (elements.front()->type != DATA_TYPE::LIST) {
        Elem* retVal = elements.front();
        elements.pop_front();
        if (retVal->type == INT) {
            outVal = new int(*reinterpret_cast<int*>(retVal->data));
        } else if (retVal->type == DOUBLE) {
            outVal = new int(*reinterpret_cast<double*>(retVal->data));
        } else if (retVal->type == STRING) {
            outVal = new std::string(*reinterpret_cast<std::string*>(retVal->data));
        }
        retType = retVal->type;
        delete retVal;
        return retType;
    }
}
