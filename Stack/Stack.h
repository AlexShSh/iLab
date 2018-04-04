#ifndef STACKCALCULATE_STACK_H
#define STACKCALCULATE_STACK_H

#include <glob.h>

#define STACK_MAX_SIZE 32

#define STACK_ASSERT(stk) stk->_assert(#stk, __PRETTY_FUNCTION__);

#define STACK_DUMP(stk) stk->_dump(#stk, __FILE__, __PRETTY_FUNCTION__, __LINE__);

typedef int value_t;

class Stack
{
private:
    value_t* data;
    size_t count;
    size_t maxCount;

public:
    Stack();
    ~Stack();
    void Push(value_t val);
    value_t Pop();
    void Add();
    void Sub();
    void Mul();
    void Div();
    void Sqr();
    void Pow();
    void Sqrt();

    void _dump(const char* stkName, const char* fileName, const char* funcName, size_t line);
    void _assert(const char* stackName, const char* funcName);

private:
    void createData();
    void resizeData();
    int IsNotOk();

};


void stack_dump(Stack* stk, const char* stkName, const char* fileName, const char* funcName, size_t line);

#endif //STACKCALCULATE_STACK_H
