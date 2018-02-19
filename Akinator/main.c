#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Node/Node.h"
#include "Akinator/Akinator.h"
#include "ExtraFunc/ExtraFunc.h"



int main()
{
    Node* tree = CreateAkinatorTree();

    printf("Enter 1 to start Akinator, 2 to make determination, 3 to make compasition, 0 to exit\n");

    char* var = (char*) calloc(1, sizeof(char));
    GetAnswer(var);
    while (*var != '0')
    {
        switch (*var)
        {
            case '1':
                Akinator(tree);
                break;
            case '2':
                makeDetermination(tree);
                break;
            case '3':
                makeCompasition(tree);
                break;
            default:
                printf("Enter the correct character!\n");
                break;
        }
        printf("Enter 1 to start Akinator, 2 to make determination, 3 to make compasition, 0 to exit\n");
        GetAnswer(var);
    }
    free(var);

    WriteAkinatorTree(tree);

    nodeDot(tree);

    nodeDelete(tree);

    return 0;
}
