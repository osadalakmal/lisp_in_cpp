#ifndef INCLUDED_EVALUATOR_H
#define INCLUDED_EVALUATOR_H

#include <elements.h>
#include <memory>

class Evaluator {
    private:
        //NOT IMPLEMENTED
        Evaluator(const Evaluator& other);
        Evaluator& operator=(const Evaluator& other);

    public:
        Evaluator() {}
        elemSet eval(elemSet element, Env* env);

};

#endif
