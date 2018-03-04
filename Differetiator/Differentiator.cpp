//
// Created by alex on 04.03.18.
//

#include <cstdio>
#include <cassert>
#include "Differentiator.h"


Node* Differentiator::Diff(Node* tree)
{
    Node* diffTree = NULL;
    switch (tree->flag)
    {
        case FUNC:
            diffTree = DiffFunc(tree);
            break;
        case VAR:
            diffTree = DiffVar(tree);
            break;
        case NUM:
            diffTree = DiffNum();
            break;
    }

    return diffTree;
}

Node* Differentiator::DiffFunc(Node *tree)
{
    assert(tree->flag == FUNC);

    Node* diffTree = NULL;
    switch (tree->value)
    {
        case SUM:
            diffTree = DiffSum(tree);
            break;
        case SUB:
            diffTree = DiffSub(tree);
            break;
        case MUL:
            diffTree = DiffMul(tree);
            break;
        case DEL:
            diffTree = DiffDel(tree);
            break;

        default:
            diffTree = NULL;
    }

    return diffTree;
}

Node* Differentiator::DiffSum(Node *tree)
{
    Node* diffTree = new Node(FUNC, SUM);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffSub(Node *tree)
{
    Node* diffTree = new Node(FUNC, SUB);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffMul(Node *tree)
{
    Node* diffTree = new Node(FUNC, SUM);

    diffTree->addLeft(FUNC, MUL);
    diffTree->left->attachLeft(Diff(tree->left));
    diffTree->left->attachRight(Copy(tree->right));

    diffTree->addRight(FUNC, MUL);
    diffTree->right->attachLeft(Copy(tree->left));
    diffTree->right->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffDel(Node *tree)
{
    Node* diffTree = new Node(FUNC, DEL);

    diffTree->addLeft(FUNC, SUB);
        diffTree->left->addLeft(FUNC, MUL);
            diffTree->left->left->attachLeft(Diff(tree->left));
            diffTree->left->left->attachRight(Copy(tree->right));
        diffTree->left->addRight(FUNC, MUL);
            diffTree->left->right->attachLeft(Diff(tree->right));
            diffTree->left->right->attachRight(Copy(tree->left));

    diffTree->addRight(FUNC, MUL);
        diffTree->right->attachLeft(Copy(tree->right));
        diffTree->right->attachRight(Copy(tree->right));

    return diffTree;
}

Node* Differentiator::DiffVar(Node *tree)
{
    assert(tree->flag == VAR);

    Node* diffTree = new Node(NUM, 1);

    return diffTree;
}

Node* Differentiator::DiffNum()
{
    Node* diffTree = new Node(NUM, 0);

    return diffTree;
}

Node* Differentiator::Copy(Node *tree)
{
    Node* newNode = new Node(tree->flag, tree->value);

    if (tree->left)
        newNode->attachLeft(Copy(tree->left));

    if (tree->right)
        newNode->attachRight(Copy(tree->right));

    return newNode;
}