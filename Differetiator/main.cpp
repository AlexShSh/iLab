#include <iostream>
#include "Node.h"
#include "Differentiator.h"
#include "TexOutput.h"
#include "Optimization.h"


int main()
{
    FILE* f = fopen("output.tex", "wt");
    TexOutput TexOut = TexOutput(f);
    TexOut.printPreambula();

    Node* tree = new Node(FUNC, MUL);
    tree->addLeft(FUNC, COS);
        tree->left->addRight(FUNC, DEL);
            tree->left->right->addLeft(FUNC, SIN);
                tree->left->right->left->addRight(VAR, X_VAR);
            tree->left->right->addRight(FUNC, LOG);
                tree->left->right->right->addRight(VAR, X_VAR);
    tree->addRight(FUNC, SUB);
        tree->right->addLeft(FUNC, TAN);
            tree->right->left->addRight(VAR, X_VAR);
        tree->right->addRight(FUNC, EXP);
            tree->right->right->addRight(FUNC, MUL);
                tree->right->right->right->addLeft(NUM, 5);
                tree->right->right->right->addRight(VAR, X_VAR);

    /*Node* tree = new Node(FUNC, TAN);
    tree->addRight(FUNC, EXP);
        tree->right->addRight(FUNC, MUL);
        tree->right->right->addLeft(NUM, 7);
        tree->right->right->addRight(FUNC, SQRT);
            tree->right->right->right->addRight(VAR, X_VAR);*/

    tree->Dot("tree-dot");
    fprintf(f, "Требуется продифференцировать данное выражение: \n\n");
    TexOut.printTree(tree);

    Differentiator Differ = Differentiator(f);
    Node* diffTree = Differ.Diff(tree);
    diffTree->Dot("diffTree-dot");

    fprintf(f, "Итак, искомая производная равна: \n\n");
    TexOut.printTree(diffTree);

    fprintf(f, "Попытаемся упростить выражение: \n\n");
    Optimization Optim = Optimization(f);
    Optim.Optimize(&diffTree);

    fprintf(f, "Итоговый результат: \\\\ \n");
    TexOut.printTree(diffTree);

    diffTree->Dot("optTree-dot");

    TexOut.printEnd();
    fclose(f);

    delete tree;
    delete diffTree;

    return 0;
}