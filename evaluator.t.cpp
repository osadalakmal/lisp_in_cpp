#include <evaluator.h>
#include "gtest/gtest.h"

class EvalFixture : public ::testing::Test {
    
public:
    Evaluator* evaluator;
    Env* env;
    std::list<Elem*> elems;

    EvalFixture() : evaluator(new Evaluator()), env(new Env()), elems() {
    }

    virtual void SetUp() {
    }

};

TEST_F(EvalFixture, Paramtest) {
    void* someVal;
    ASSERT_NO_THROW(evaluator->eval(elems, env, someVal));
}

TEST_F(EvalFixture, ConstDeftest) {
    Elem* elem = new Elem();
    elem->type = DATA_TYPE::INT;
    elem->size = sizeof(int);
    elem->data = new int(5);
    elems.push_back(elem);
    void* outData;
    ASSERT_NO_THROW(evaluator->eval(elems, env, outData));
    ASSERT_EQ(*reinterpret_cast<int*>(outData),5);
}

