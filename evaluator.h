#ifndef INCLUDED_EVALUATOR_H
#define INCLUDED_EVALUATOR_H

#include <elements.h>
#include <list>

class Evaluator {
    private:
        //NOT IMPLEMENTED
        Evaluator(const Evaluator& other);
        Evaluator& operator=(const Evaluator& other);

    public:
        Evaluator() {}
        DATA_TYPE eval(std::list<Elem*>& elements, Env* env, void*& outVal);
};

#endif
