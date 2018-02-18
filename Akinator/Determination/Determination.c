#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Node/Node.h"
#include "../Akinator/Akinator.h"
#include "../Stack/Stack.h"


void makeDetermination(Node* tree)
{
    printf("Enter a name of object\n");

    char* name_buf = (char*) calloc(BUFF_SIZE, sizeof(char));

    GetAnswer(name_buf);

    Node* res = nodeFind(tree, name_buf);

    if (res == NULL)
    {
        printf("I don't know this object!\n");
        return;
    }

    Stack* stk = stack_create();

    while (res->parent)
    {
        res = res->parent;
        stack_push(stk, res);
    }

    printf("%s is ", name_buf);
    Node* cur = stack_pop(stk);
    Node* next = stack_pop(stk);

    while (next)
    {
        if (strcmp(next->value, cur->right->value) == 0)
            printf("not %s, ", cur->value);
        else
            printf("%s, ", cur->value);

        cur = next;
        next = stack_pop(stk);
    }
}
