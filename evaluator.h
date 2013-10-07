#ifndef INCLUDED_EVALUATOR_H
#define INCLUDED_EVALUATOR_H

#include <elements.h>

class Evaluator {
    private:
        //NOT IMPLEMENTED
        Evaluator(const Evaluator& other);
        Evaluator& operator=(const Evaluator& other);

    public:
        Evaluator() {}
        Elem* eval(std::shared_ptr<Elem> elements, Env* env);
};

#endif
