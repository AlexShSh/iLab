#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Stack.h"


Stack* stack_create()
{
    Stack* stk = (Stack*) calloc(1, sizeof(Stack));
    stk->data = NULL;
    stk->count = 0;
    stk->maxCount = 0;

    assert(stack_ok(stk));

    return stk;
}


Stack* createBuffer(Stack* stk)
{
    assert(stack_ok(stk));

    stk->maxCount = STACK_SIZE;
    stk->data = (int*) calloc(stk->maxCount, sizeof(int));

    assert(stack_ok(stk));

    return stk;
}


Stack* resizeBuffer(Stack* stk)
{
    assert(stack_ok(stk));

    stk->maxCount *= 2;
    stk->data = (int*) realloc(stk->data ,stk->maxCount * sizeof(int));

    assert(stack_ok(stk));

    return stk;
}


int stack_ok(Stack* stk)
{
    if (stk == NULL)
        return 0;
    return stk->data && stk->maxCount > 0 && stk->count >= 0 && stk->count <= stk->maxCount
           ||
           !stk->data && !stk->maxCount && !stk->count;
}

void stack_push(Stack* stk, int value)
{
    assert(stack_ok(stk));

    if (stk->data == NULL)
        stk = createBuffer(stk);

    if (stk->count == stk->maxCount)
        stk = resizeBuffer(stk);

    stk->data[stk->count++] = value;

    assert(stack_ok(stk));
}


int stack_pop(Stack* stk)
{
    assert(stack_ok(stk));

    int value = stk->data[--stk->count];

    assert(stack_ok(stk));

    return value;
}


void stack_delete(Stack* stk)
{
    assert(stack_ok(stk));

    free(stk->data);
    free(stk);
}


void stack_dump(Stack* stk)
{
    assert(stack_ok(stk));
    int i = 0;
    printf("{\n\tcount = %d \n\tmaxCount = %d \n\tbuf[0x%p]\n\t{\n", stk->count, stk->maxCount, stk->data);
    for (i = 0; i < stk->maxCount; ++i)
    {
        if (i < stk->count)
            printf("\t\t*");
        else
            printf("\t\t ");
        printf("[%d] = %d\n", i, stk->data[i]);
    }
    printf("\t}\n}\n");
}