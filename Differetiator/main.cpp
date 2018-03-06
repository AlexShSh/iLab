#include <iostream>
#include "Node.h"
#include "Differentiator.h"


int main()
{
    auto tree = new Node(FUNC, DEL);

    tree->addLeft(NUM, 1);
    tree->addRight(FUNC, DEL);
        tree->right->addLeft(NUM, 1);
        tree->right->addRight(VAR, X_VAR);

    auto ntree = new Node(FUNC, SIN);
    ntree->attachRight(tree);

    auto Differ = Differentiator();

    Node* diffTree = Differ.Diff(ntree);

    ntree->Dot("tree");
    diffTree->Dot("diffTree");

    delete ntree;
    delete diffTree;

    return 0;
}