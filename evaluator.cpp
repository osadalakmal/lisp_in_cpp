#include <evaluator.h>
#include <cassert>
#include <stdexcept>
#include <memory>

using namespace std;

Elem* Evaluator::eval(std::shared_ptr<Elem> element, Env* env) {
    assert(env);
    if (element->type == DATA_TYPE::NILL) {
        Elem* retVal = new Elem();
        retVal->type = DATA_TYPE::NILL;
        return retVal;
    } else if (element->type == SYMBOL) {
        Elem* retVal = new Elem();
        assert((*element->valList).size() == 0);
        Env* foundEnv = env->findInHier(element->valStr);
        if (foundEnv != nullptr) {
            switch ((*foundEnv)[element->valStr]->type) {
                case DATA_TYPE::INT:
                    retVal->valInt = (*foundEnv)[element->valStr]->valInt;
                    retVal->type = DATA_TYPE::INT;
                case DATA_TYPE::DOUBLE:
                    retVal->valDbl = (*foundEnv)[element->valStr]->valDbl;
                    retVal->type = DATA_TYPE::DOUBLE;
                case DATA_TYPE::STRING:
                    retVal->valStr = (*foundEnv)[element->valStr]->valStr;
                    retVal->type = DATA_TYPE::STRING;
                default:
                    throw new std::runtime_error("Incoorect type for data");
            }
            return retVal;
        } else {
            throw new std::runtime_error("No Env with Given Var");
        }
    }/* else if (element->type == DATA_TYPE::INT ||
               element->type == DATA_TYPE::STRING ||
               element->type == DATA_TYPE::DOUBLE) {
        return element->data;
    } else if (element->type == QUOTE) {
        return element->data;
    } else if (elements->front()->type == SET) {
        auto elemList = reinterpret_cast<std::list<Elem>*>(elements->front()->data);
        std::string* varName = reinterpret_cast<std::string*>(elemList->front().data);
        elemList->pop_front();
        env->d_vars[*varName] = std::shared_ptr<Elem>(new Elem(elemList->front()));
        elemList->pop_front();
        return env->d_vars[*varName]->type;
    }*/
}
