#include <stdio.h>
#include "Node/Node.h"
#include "Akinator/Akinator.h"
#include "Determination/Determination.h"



int main()
{
    Node* tree = CreateAkinatorTree();


    makeDetermination(tree);
    /*
    printf("Enter 1 to start Akinator, 2 to make determination, 0 to exit\n");

    int var = 0;
    scanf("%d", &var);
    while (var)
    {
        switch (var)
        {
            case 1:
                Akinator(tree);
                break;
            case 2:
                makeDetermination(tree);
                break;
            default:
                printf("Enter the correct character!\n");
        }
        printf("Enter 1 to start Akinator, 2 to make determination, 0 to exit\n");
        scanf("%d", &var);
    }
    */

    WriteAkinatorTree(tree);

    nodeDot(tree);

    nodeDelete(tree);

    return 0;
}
