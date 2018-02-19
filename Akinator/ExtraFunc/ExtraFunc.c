#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Node/Node.h"
#include "../Akinator/Akinator.h"
#include "../Stack/Stack.h"
#include "ExtraFunc.h"


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

    Stack* stk = makeStack(res);

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


void makeCompasition(const Node* tree)
{
    printf("Enter a name of first object\n");
    char* name_buf1 = (char*) calloc(BUFF_SIZE, sizeof(char));
    GetAnswer(name_buf1);
    Node* res1 = nodeFind(tree, name_buf1);
    if (res1 == NULL)
    {
        printf("I don't know this object!\n");
        return;
    }

    printf("Enter a name of second object\n");
    char* name_buf2 = (char*) calloc(BUFF_SIZE, sizeof(char));
    GetAnswer(name_buf2);
    Node* res2 = nodeFind(tree, name_buf2);
    if (res2 == NULL)
    {
        printf("I don't know this object!\n");
        return;
    }

    Stack* stk1 = makeStack(res1);
    Stack* stk2 = makeStack(res2);

    Node* cur1 = stack_pop(stk1);
    Node* cur2 = stack_pop(stk2);
    Node* next1 = stack_pop(stk1);
    Node* next2 = stack_pop(stk2);

    if (strcmp(next1->value, cur1->left->value) == 0 &&  strcmp(next2->value, cur2->left->value) == 0 ||
        strcmp(next1->value, cur1->right->value) == 0 && strcmp(next2->value, cur2->right->value) == 0 )
            printf("They are ");

    while ((strcmp(next1->value, cur1->left->value) == 0 &&  strcmp(next2->value, cur2->left->value) == 0 ||
           strcmp(next1->value, cur1->right->value) == 0 && strcmp(next2->value, cur2->right->value) == 0) && next1 && next2)
    {
        if (strcmp(next1->value, cur1->right->value) == 0)
        printf("not %s, ", cur1->value);
        else
        printf("%s, ", cur1->value);

        cur1 = next1;
        cur2 = next2;
        next1 = stack_pop(stk1);
        next2 = stack_pop(stk2);
    }

    if (!next1 || !next2)
        return;

    printf("but %s is ", name_buf1);
    while (next1)
    {
        if (strcmp(next1->value, cur1->right->value) == 0)
            printf("not %s, ", cur1->value);
        else
            printf("%s, ", cur1->value);

        cur1 = next1;
        next1 = stack_pop(stk1);
    }

    printf("but %s is ", name_buf2);
    while (next2)
    {
        if (strcmp(next2->value, cur2->right->value) == 0)
            printf("not %s, ", cur2->value);
        else
            printf("%s, ", cur2->value);

        cur2 = next2;
        next2 = stack_pop(stk2);
    }

}


Stack* makeStack(const Node* node)
{
    Stack* stk = stack_create();

    while (node->parent)
    {
        node = node->parent;
        stack_push(stk, node);
    }

    return stk;
}