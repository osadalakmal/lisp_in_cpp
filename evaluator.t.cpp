#include <evaluator.h>
#include <parser.h>
#include "gtest/gtest.h"

class EvalFixture : public ::testing::Test {
    
public:
    Evaluator* evaluator;
    Env* global;
    Env* env;
    std::shared_ptr<Elem> elems;

    EvalFixture() : evaluator(new Evaluator()), global(new Env(NULL)), 
                    env(new Env(global)), elems(new Elem()) {
    }

    virtual void SetUp() {
    }

};

TEST_F(EvalFixture, Paramtest) {
    void* someVal;
    ASSERT_NO_THROW(evaluator->eval(elems, env));
}

TEST_F(EvalFixture, ConstDeftest) {
    std::shared_ptr<Elem> intElem(new Elem());
    makeInt(intElem,5);
    env->insert("variable",intElem);
    std::shared_ptr<Elem> varElem(new Elem());
    makeSymb(varElem,"variable");
    elemSet res = evaluator->eval(varElem, env);
    ASSERT_EQ(res[0]->type,DATA_TYPE::INT);
    ASSERT_EQ(res[0]->valInt,5);
}

TEST_F(EvalFixture, QuoteTest) {
    Parser parser("(quote ((1) (2)))");
    boost::sregex_token_iterator it = parser.Tokenize();
    boost::sregex_token_iterator j;
    it++;
    elemSet result;
    ASSERT_NO_THROW(result = parser.readFromTokens(it,j));
    std::cout << result[0] << std::endl;
    auto res = evaluator->eval(result[0], env);
    //ASSERT_EQ(res->type,DATA_TYPE::STRING);
    //ASSERT_STREQ(res->valStr.c_str(),"osada");
}

/*TEST_F(EvalFixture, SetDefTest) {
    std::shared_ptr<Elem> strElem(new Elem());
    makeStr(strElem, "osada");
    std::shared_ptr<Elem> symbElem(new Elem());
    makeSymb(symbElem, "variable");
    symbElem->valExp = strElem;
    std::shared_ptr<Elem> setElem(new Elem());
    makeOP(DATA_TYPE::SET, setElem, symbElem);
    std::shared_ptr<Elem> res;
    ASSERT_THROW(evaluator->eval(setElem, env),std::runtime_error);
    std::shared_ptr<Elem> defElem(new Elem());
    makeOP(DATA_TYPE::DEFINE, defElem, symbElem);
    ASSERT_NO_THROW(res = evaluator->eval(defElem, env));
    ASSERT_EQ(res->type,DATA_TYPE::STRING);
    ASSERT_STREQ(res->valStr.c_str(),"osada");
}*/

/*TEST_F(EvalFixture, SetDefTest) {
    std::shared_ptr<Elem> strElem(new Elem());
    makeStr(strElem, "osada");
    std::shared_ptr<Elem> symbElem(new Elem());
    makeSymb(symbElem, "variable");
    symbElem->valExp = strElem;
    std::shared_ptr<Elem> setElem(new Elem());
    makeOP(DATA_TYPE::SET, setElem, symbElem);
    std::shared_ptr<Elem> res;
    ASSERT_THROW(evaluator->eval(setElem, env),std::runtime_error);
    std::shared_ptr<Elem> defElem(new Elem());
    makeOP(DATA_TYPE::DEFINE, defElem, symbElem);
    ASSERT_NO_THROW(res = evaluator->eval(defElem, env));
    ASSERT_EQ(res->type,DATA_TYPE::STRING);
    ASSERT_STREQ(res->valStr.c_str(),"osada");
}*/



