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
    Node* Diff(Node* tree);

private:
    Node* DiffFunc(Node* tree);
    Node* DiffVar(Node* tree);
    Node* DiffNum();

    Node* DiffSum(Node* tree);
    Node* DiffSub(Node* tree);
    Node* DiffMul(Node* tree);
    Node* DiffDel(Node* tree);

    Node* Copy(Node* tree);
};


#endif //NODECLASS_DIFFERENTIATOR_H
