#include <evaluator.h>
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

/*TEST_F(EvalFixture, ConstDeftest) {
    elems->type = DATA_TYPE::INT;
    elems->data = 5;
    DATA data = evaluator->eval(elems, env);
    ASSERT_EQ(data,DATA(5));
}

TEST_F(EvalFixture, QuoteTest) {
    elems->type = DATA_TYPE::QUOTE;
    Elem* dataElem = new Elem();
    dataElem->type = DATA_TYPE::SYMBOL;
    dataElem->str = "variable";
    dataElem->data = "osada";
    //std::shared_ptr<DATA> dataPtr(dataElem);
    elems->data = std::shared_ptr<DATA>();//dataPtr;
    DATA data = evaluator->eval(elems, env);
    std::list<Elem>& elemList = *(reinterpret_cast<std::list<Elem>*>(outData));
    ASSERT_EQ(elemList.front().type,DATA_TYPE::SYMBOL);
    ASSERT_STREQ(reinterpret_cast<std::string*>(elemList.front().data)->c_str(),"variable");
    elemList.pop_front();
    ASSERT_EQ(elemList.front().type,DATA_TYPE::STRING);
    ASSERT_STREQ(reinterpret_cast<std::string*>(elemList.front().data)->c_str(),"osada");
}*/

/*TEST_F(EvalFixture, SetTest) {
    Elem* elem = new Elem();
    elem->type = DATA_TYPE::SET;
    elem->size = sizeof(int);
    elem->data = new std::list<Elem>();
    Elem symb;
    symb.type = DATA_TYPE::SYMBOL;
    symb.data = new std::string("variable");
    symb.size = sizeof(*(symb.data));
    Elem val;
    val.type = DATA_TYPE::STRING;
    val.data = new std::string("osada");
    val.size = sizeof(*(symb.data));
    reinterpret_cast<std::list<Elem>* >(elem->data)->push_back(symb);
    reinterpret_cast<std::list<Elem>* >(elem->data)->push_back(val);
    elems.push_back(elem);
    void* outData = nullptr;
    auto var1 = (*env)[std::string("variable")];
    ASSERT_EQ(bool(var1),false);
    evaluator->eval(&elems, env, outData);
    ASSERT_EQ(outData,nullptr);
    std::shared_ptr<Elem> var2 = (*env)["variable"];
    ASSERT_EQ(var1->type,DATA_TYPE::STRING);
    ASSERT_STREQ(reinterpret_cast<std::string*>(var1->data)->c_str(),"osada");
}*/

/*TEST_F(EvalFixture, SetTest) {
    Elem* elem = new Elem();
    elem->type = DATA_TYPE::DEFINE;
    elem->size = sizeof(int);
    elem->data = new std::list<Elem>();
    Elem symb;
    symb.type = DATA_TYPE::SYMBOL;
    symb.data = new std::string("variable");
    symb.size = sizeof(*(symb.data));
    Elem val;
    val.type = DATA_TYPE::STRING;
    val.data = new std::string("osada");
    val.size = sizeof(*(symb.data));
    reinterpret_cast<std::list<Elem>* >(elem->data)->push_back(symb);
    reinterpret_cast<std::list<Elem>* >(elem->data)->push_back(val);
    elems.push_back(elem);
    void* outData = nullptr;
    auto var1 = env[std::string("variable")];
    ASSERT_EQ(var1,false);
    evaluator->eval(&elems, env, outData);
    ASSERT_EQ(outData,nullptr);
    auto var2 = *(env["variable"]);
    ASSERT_EQ(var1->type,DATA_TYPE::STRING);
    ASSERT_STREQ(reinterpret_cast<std::string*>(var1->data)->c_str(),"osada");

}

TEST_F(EvalFixture, VarDefTest) {
    Elem* elem = new Elem();
    elem->type = DATA_TYPE::DEFINE;
    elem->size = sizeof(int);
    elem->data = new std::list<Elem>(2);
    Elem* symb = new Elem();
    symb->type = DATA_TYPE::SYMBOL;
    symb->data = new std::string("variable");
    symb->size = sizeof(*symb->data);
    Elem* val = new Elem();
    symb->type = DATA_TYPE::STRING;
    symb->data = new std::string("osada");
    symb->size = sizeof(*symb->data);
    elem->data->push_back(symb);
    elem->data->push_back(val);
    elems.push_back(elem);
    void* outData = NULL;
    ASSERT_NO_THROW(evaluator->eval(elems, env, outData));
    ASSERT_EQ(*reinterpret_cast<int*>(outData),5);
    ASSERT_EQ(elems.size(),0);
}*/

