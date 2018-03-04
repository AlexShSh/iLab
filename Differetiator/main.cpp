#include <cstdio>
#include "Node.h"
#include "Differentiator.h"


int main()
{
    Node* tree = new Node(FUNC, DEL);

    tree->addLeft(NUM, 1);
    tree->addRight(FUNC, DEL);
        tree->right->addLeft(NUM, 1);
        tree->right->addRight(VAR, X_VAR);

    auto Differ = new Differentiator;

    Node* diffTree = Differ->Diff(tree);

    diffTree->Dot();

    return 0;
}