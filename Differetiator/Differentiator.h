#ifndef NODECLASS_DIFFERENTIATOR_H
#define NODECLASS_DIFFERENTIATOR_H

#include <cstdio>
#include "Node.h"
#include "TexOutput.h"

class Differentiator
{

private:
    TexOutput TexOut;
public:
    Differentiator(FILE* f);
    Node* Diff(const Node* tree);

private:
    Node* DiffFunc(const Node* tree);
    Node* DiffVar(const Node* tree);
    Node* DiffNum(const Node* tree);

    Node* DiffSum(const Node* tree);
    Node* DiffSub(const Node* tree);
    Node* DiffMul(const Node* tree);
    Node* DiffDel(const Node* tree);
    Node* DiffSin(const Node* tree);
    Node* DiffCos(const Node* tree);
    Node* DiffLog(const Node* tree);
    Node* DiffTan(const Node* tree);
    Node* DiffCot(const Node *tree);
    Node* DiffSqrt(const Node* tree);
    Node* DiffExp(const Node* tree);

    Node* Copy(const Node* tree);
};


#endif //NODECLASS_DIFFERENTIATOR_H
