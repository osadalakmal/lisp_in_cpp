#include <evaluator.h>
#include <cassert>
#include <stdexcept>

using namespace std;

std::shared_ptr<Elem> Evaluator::eval( std::shared_ptr<Elem> element, Env* env) {
    assert(env);
    if (element->type == DATA_TYPE::NILL) {
        std::shared_ptr<Elem> retVal(new Elem());
        retVal->type = DATA_TYPE::NILL;
        return retVal;
    } else if (element->type == SYMBOL) {
        std::shared_ptr<Elem> retVal(new Elem());
        assert(bool(element->valExp) == false);
        Env* foundEnv = env->findInHier(element->valStr);
        std::shared_ptr<Elem> foundElem = (*foundEnv)[element->valStr];
        if (bool(foundEnv) != false) {
            switch (foundElem->type) {
                case DATA_TYPE::INT:
                    retVal->valInt = foundElem->valInt;
                    retVal->type = DATA_TYPE::INT;
                    break;
                case DATA_TYPE::DOUBLE:
                    retVal->valDbl = foundElem->valDbl;
                    retVal->type = DATA_TYPE::DOUBLE;
                    break;
                case DATA_TYPE::STRING:
                    retVal->valStr = foundElem->valStr;
                    retVal->type = DATA_TYPE::STRING;
                    break;
                default:
                    throw std::runtime_error("Incoorect type for data");
                    break;
            }
            return retVal;
        } else {
            throw std::runtime_error("No Env with Given Var");
        }
    } else if (element->type == DATA_TYPE::INT ||
               element->type == DATA_TYPE::STRING ||
               element->type == DATA_TYPE::DOUBLE) {
        return element;
    } else if (element->type == QUOTE) {
        return element->valExp;
    } else if (element->type == SET) {
        assert(bool(element->valExp) == true);
        auto symbElement = element->valExp;
        assert(bool(symbElement->valExp) == true);
        Env* foundEnv = env->findInHier(symbElement->valStr);
        if (foundEnv != nullptr) {
            std::shared_ptr<Elem>& foundElem = (*foundEnv)[symbElement->valStr];
            foundElem = symbElement->valExp;
            return foundElem;
        } else {
            throw std::runtime_error("No Env with Given Var");
        }
    } else if (element->type == DEFINE) {
        assert(bool(element->valExp) == true);
        auto symbElement = element->valExp;
        assert(bool(symbElement->valExp) == true);
        (*env)[symbElement->valStr] = symbElement->valExp;
        return (*env)[symbElement->valStr];
    }
}
