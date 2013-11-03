#include <evaluator.h>
#include <cassert>
#include <stdexcept>

using namespace std;

elemSet Evaluator::eval( std::shared_ptr<Elem> element, Env* env) {
    assert(env);
    std::vector<std::shared_ptr<Elem> > retVec;
    if (element->type == DATA_TYPE::NILL) {
        std::shared_ptr<Elem> retVal(new Elem());
        retVal->type = DATA_TYPE::NILL;
        retVec.push_back(retVal);
        return retVec;
    } else if (element->type == SYMBOL) {
        std::shared_ptr<Elem> retVal(new Elem());
        assert(element->valExp.size() == 0);
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
                    throw std::runtime_error("Incorect type for data");
                    break;
            }
            retVec.push_back(retVal);
            return retVec;
        } else {
            throw std::runtime_error("No Env with Given Var");
        }
    } else if (element->type == DATA_TYPE::INT ||
               element->type == DATA_TYPE::STRING ||
               element->type == DATA_TYPE::DOUBLE) {
        retVec.push_back(element);
        return retVec;
    } else if (element->type == QUOTE) {
        return element->valExp;
    } else if (element->type == SET) {
        assert(element->valExp.size() == 0);
        auto symbElement = eval(element->valExp,env);
        Env* foundEnv = env->findInHier(element->valStr);
        if (foundEnv != nullptr) {
            (*foundEnv)[element->valStr] = symbElement[0];
            return retVec;
        } else {
            throw std::runtime_error("No Env with Given Var");
        }
    } else {
        throw std::runtime_error("I dont know what to do!!");
    }
}

std::vector<std::shared_ptr<Elem> > Evaluator::eval( 
        std::vector<std::shared_ptr<Elem> > element, Env* env) {
    
    /*if (element->type == DEFINE) {
        assert(bool(element->valExp) == true);
        auto symbElement = element->valExp;
        assert(bool(symbElement->valExp) == true);
        (*env)[symbElement->valStr] = symbElement->valExp;
        retVec.push_back((*env)[symbElement->valStr]);
        return retVec;
    }*/
}
