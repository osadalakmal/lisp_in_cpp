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
        if (foundEnv != nullptr) {
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
                    throw new std::runtime_error("Incoorect type for data");
                    break;
            }
            return retVal;
        } else {
            throw new std::runtime_error("No Env with Given Var");
        }
    } else if (element->type == DATA_TYPE::INT ||
               element->type == DATA_TYPE::STRING ||
               element->type == DATA_TYPE::DOUBLE) {
        return element;
    } else if (element->type == QUOTE) {
        return element->valExp;
    }/* else if (elements->front()->type == SET) {
        auto elemList = reinterpret_cast<std::list<Elem>*>(elements->front()->data);
        std::string* varName = reinterpret_cast<std::string*>(elemList->front().data);
        elemList->pop_front();
        env->d_vars[*varName] = std::shared_ptr<Elem>(new Elem(elemList->front()));
        elemList->pop_front();
        return env->d_vars[*varName]->type;
    }*/
}
