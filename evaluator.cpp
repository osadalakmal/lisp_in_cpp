#include <evaluator.h>
#include <cassert>
#include <stdexcept>

using namespace std;

ElementSet Evaluator::eval( const ElementSet& elements, Env* env) {
    assert(env);
    std::vector<std::shared_ptr<Elem> > retVec;
    if(elements.size() >= 1) {
    	auto element = elements[0];
        if (element->type == DATA_TYPE::NILL) {
            std::shared_ptr<Elem> retVal(new Elem());
            retVal->type = DATA_TYPE::NILL;
            retVec.push_back(retVal);
            return retVec;
        } else if (element->type == SYMBOL) {
            std::shared_ptr<Elem> retVal(new Elem());
            assert(element->valExp.size() == 0);
            Env* foundEnv = env->findInHier(element->valStr);
            if (!foundEnv)
            	throw std::runtime_error("No such variable found:" + element->valStr);
            auto map = foundEnv->getMap();
            for_each(map.begin(),map.end(),[](std::pair<const std::basic_string<char>, std::shared_ptr<Elem> > i) { std::cout << "key:" << i.first << " val:" << i.second << std::endl; });
            std::shared_ptr<Elem> foundElem = foundEnv->find(element->valStr);
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
        	retVec.assign(elements.begin()+1, elements.end());
            return retVec;
        } else if (element->type == SET) {
            assert(element->valExp.size() == 2);
            auto elementVar = element->valExp[0];
            auto elementVal = element->valExp[1];
            Env* foundEnv = env->findInHier(elementVar->valStr);
            if (foundEnv == nullptr) {
                env->insert(elementVar->valStr,elementVal);
                return retVec;
            } else {
                throw std::runtime_error("No Env with Given Var");
            }
        } else if (element->type == DATA_TYPE::PROC) {
        	auto retVal = eval(element->valExp, env);
        	retVec.insert(retVec.end(), retVal.begin(), retVal.end());
        	return retVec;
        } else {
            throw std::runtime_error("I dont know what to do!!");
        }
    }
    return retVec;
}

