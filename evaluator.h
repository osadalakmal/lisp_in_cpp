#ifndef INCLUDED_EVALUATOR_H
#define INCLUDED_EVALUATOR_H

#include <elements.h>
#include <memory>

class StatementHelper {

    static inline std::shared_ptr<Elem> getSetCmd(const std::string varName, int val) {
        std::shared_ptr<Elem> elementOp = std::make_shared<Elem>();
        elementOp->type = DATA_TYPE::SET;
        std::shared_ptr<Elem> element = std::make_shared<Elem>();
        element->valStr = varName;
        std::shared_ptr<Elem> elementVal = std::make_shared<Elem>();
        elementVal->valInt = val;
        elementVal->type = INT;
        elementOp->valExp.push_back(element);
        elementOp->valExp.push_back(elementVal);
    }

};

class Evaluator {
    private:
        //NOT IMPLEMENTED
        Evaluator(const Evaluator& other);
        Evaluator& operator=(const Evaluator& other);

    public:
        Evaluator() {}
        ElementSet eval(ElementSet element, Env* env);

};

#endif
