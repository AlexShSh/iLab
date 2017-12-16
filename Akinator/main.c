#include <stdio.h>
#include "Akinator.h"
#include "Node.h"


int main()
{
    Node* tree = CreateAkinatorTree();

    Akinator(tree);

    WriteAkinatorTree(tree);

    nodeDot(tree);

    nodeDelete(tree);

    return 0;
}
