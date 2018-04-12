#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include "Stack.h"

Stack::Stack():
    data(nullptr),
    count(0),
    maxCount(0) {}

Stack::~Stack()
{
    delete[] data;
    data = nullptr;
}

void Stack::Push(value_t val)
{
    STACK_ASSERT(this);

    if (data == nullptr)
        createData();

    if (maxCount == count)
        resizeData();

    data[count] = val;
    count++;

    STACK_ASSERT(this);
}

value_t Stack::Pop()
{
    STACK_ASSERT(this);

    count--;
    int value = data[count];

    STACK_ASSERT(this);

    return value;
}

void Stack::Add()
{
    int a = Pop();
    int b = Pop();
    Push(a + b);
}

void Stack::Sub()
{
    int a = Pop();
    int b = Pop();
    Push(b - a);
}

void Stack::Mul()
{
    int a = Pop();
    int b = Pop();
    Push(a * b);
}

void Stack::Div()
{
    int a = Pop();
    int b = Pop();
    Push(b / a);
}

void Stack::Pow()
{
    int n = Pop();
    int a = Pop();
    int res = a;
    for (int i = 1; i < n; i++)
    {
        res *= a;
    }
    Push(res);
}

void Stack::Sqr()
{
    int a = Pop();
    Push(a * a);
}

void Stack::Sqrt()
{
    int a = Pop();
    a = (int) sqrt(a);
    Push(a);
}



void Stack::createData()
{
    data = new value_t[STACK_MAX_SIZE];
    assert(data && "The memory allocation error");
    maxCount = STACK_MAX_SIZE;
}

void Stack::resizeData()
{
    maxCount *= 2;
    value_t* newData = new value_t[maxCount];
    assert(newData && "The memory allocation error");
    memcpy(newData, data, count);
    delete data;
    data = newData;
}

ERROR_CODE Stack::IsNotOk()
{
    if (data && maxCount <= 0)
        return MCOUNT_L_N;
    if (!data && maxCount > 0)
        return MCOUNT_G_N;
    if (!data && count > 0)
        return COUNT_G_N;
    if (data && count < 0)
        return COUNT_L_N;
    if (data && count > maxCount)
        return COUNT_G_MCOUNT;

    return NO_ERROR;
}


void Stack::_assert(const char* stackName, const char* funcName)
{
    ERROR_CODE code = IsNotOk();
    if (code == NO_ERROR)
        return;

    printf("Stack %s [%p] error from %s:\n", stackName, this, funcName);
    switch (code)
    {
        case MCOUNT_L_N:
            printf("maxCount <= 0 but data isn't nullptr\n");
            break;
        case MCOUNT_G_N:
            printf("maxCount > 0 but data is nullptr\n");
            break;
        case COUNT_G_N:
            printf("count > 0 but data is nullptr\n");
            break;
        case COUNT_L_N:
            printf("count < 0\n"
                           "count = %d", count);
            break;
        case COUNT_G_MCOUNT:
            printf("count > maxCount\n"
                           "count = %d, maxCount = %d\n", count, maxCount);
            break;

        default:
            printf("Unknown error, code: %d\n", code);

    }
    assert(false);
}

void Stack::_dump(const char* stkName, const char* fileName, const char* funcName, size_t line)
{
    STACK_ASSERT(this);

    printf("Stack %s [%p] from %s, %s (%d)\n", stkName, this, fileName, funcName, line);

    int i = 0;
    printf("{\n\tcount = %d \n\tmaxCount = %d \n\tdata[%p]\n\t{\n", count, maxCount, data);
    for (i = 0; i < maxCount; ++i)
    {
        if (i >= count)
            printf("\t\t*");
        else
            printf("\t\t ");
        printf("[%d] = %d\n", i, data[i]);
    }
    printf("\t}\n}\n");
}