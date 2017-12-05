#pragma once

#define STACK_SIZE 16

#define DUMP(stk) printf("Stack \"" #stk "\" [0x%p] from %s %s() (%d)\n", stk, __FILE__, __PRETTY_FUNCTION__, __LINE__);\
                    stack_dump(stk);


typedef struct Stack
{
    int* data;
    unsigned int count;
    unsigned int maxCount;
} Stack;


Stack* stack_create();
Stack* createBuffer(Stack* stk);
Stack* resizeBuffer(Stack* stk);
void stack_push(Stack* stk, int value);
int stack_pop(Stack* stk);
int stack_ok(Stack* stk);
void stack_delete(Stack* stk);
void stack_dump(Stack* stk);
