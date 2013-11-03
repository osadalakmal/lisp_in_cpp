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
        elemSet eval(std::shared_ptr<Elem> elements, Env* env);
        elemSet eval(std::vector<std::shared_ptr<Elem> > element, Env* env);

};

#endif
