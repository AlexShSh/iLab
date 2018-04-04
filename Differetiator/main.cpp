#include <iostream>
#include "Node.h"
#include "Differentiator.h"
#include "TexOutput.h"
#include "Optimization.h"
#include "RDParser.h"


int main()
{
    FILE* f = fopen("output.tex", "wt");
    TexOutput TexOut = TexOutput(f);
    TexOut.printPreambula();

    RDParser RDP = RDParser("cos(sin(x) / ln(x)) * (tan(x) - exp(x))");
    Node* tree = RDP.CreateNode();

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