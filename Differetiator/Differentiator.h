//
// Created by alex on 04.03.18.
//

#ifndef NODECLASS_DIFFERENTIATOR_H
#define NODECLASS_DIFFERENTIATOR_H

#include <cstdio>
#include "Node.h"

class Differentiator
{
public:
    Node* Diff(const Node* tree);

private:
    Node* DiffFunc(const Node* tree);
    Node* DiffVar(const Node* tree);
    Node* DiffNum();

    Node* DiffSum(const Node* tree);
    Node* DiffSub(const Node* tree);
    Node* DiffMul(const Node* tree);
    Node* DiffDel(const Node* tree);
    Node* DiffSin(const Node* tree);
    Node* DiffCos(const Node* tree);
    Node* DiffLog(const Node* tree);

    Node* Copy(const Node* tree);
};


#endif //NODECLASS_DIFFERENTIATOR_H
