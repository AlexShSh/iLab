#include <stdio.h>
#include "Stack.h"


int main()
{
    Stack* stk = stack_create();

    int i = 0;

    for (i = 0; i < 7; i++)
    {
        stack_push(stk, i);
    }

    for (i = 0; i < 3; i++)
    {
        stack_pop(stk);
    }

    DUMP(stk);

    stack_delete(stk);

    return 0;
}
