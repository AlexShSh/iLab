#pragma once

#include "../Node/Node.h"

#define STACK_SIZE 16

#define DUMP(stk) printf("Stack \"" #stk "\" [0x%p] from %s %s() (%d)\n", stk, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
                    stack_dump(stk);

typedef Node* value_t;

typedef struct Stack
{
    value_t* data;
    unsigned int count;
    unsigned int maxCount;
} Stack;


Stack* stack_create();
Stack* createBuffer(Stack* stk);
Stack* resizeBuffer(Stack* stk);
void stack_push(Stack* stk, value_t value);
value_t stack_pop(Stack* stk);
int stack_ok(Stack* stk);
void stack_delete(Stack* stk);
void stack_dump(Stack* stk);
