#include <cstdio>
#include <cassert>
#include "Differentiator.h"


Node* Differentiator::Diff(const Node* tree)
{
    Node* diffTree = nullptr;
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

Node* Differentiator::DiffFunc(const Node *tree)
{
    assert(tree->flag == FUNC);

    Node* diffTree = nullptr;
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
        case SIN:
            diffTree = DiffSin(tree);
            break;
        case COS:
            diffTree = DiffCos(tree);
            break;
        case LOG:
            diffTree = DiffLog(tree);
            break;

        default:
            diffTree = nullptr;
    }

    return diffTree;
}

Node* Differentiator::DiffSum(const Node *tree)
{
    assert(tree->left && tree->right);

    Node* diffTree = new Node(FUNC, SUM);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffSub(const Node *tree)
{
    assert(tree->left && tree->right);

    Node* diffTree = new Node(FUNC, SUB);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffMul(const Node *tree)
{
    assert(tree->left && tree->right);

    Node* diffTree = new Node(FUNC, SUM);

    diffTree->addLeft(FUNC, MUL);
    diffTree->left->attachLeft(Diff(tree->left));
    diffTree->left->attachRight(Copy(tree->right));

    diffTree->addRight(FUNC, MUL);
    diffTree->right->attachLeft(Copy(tree->left));
    diffTree->right->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffDel(const Node *tree)
{
    assert(tree->left && tree->right);

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

Node* Differentiator::DiffSin(const Node *tree)
{
    assert(tree->right && !tree->left);

    Node* diffTree = new Node(FUNC, MUL);

    diffTree->addLeft(FUNC, COS);
        diffTree->left->attachRight(Copy(tree->right));

    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffCos(const Node *tree)
{
    assert(tree->right && !tree->left);

    Node* diffTree = new Node(FUNC, SUB);

    diffTree->addLeft(NUM, 0);
    diffTree->addRight(FUNC, MUL);
        diffTree->right->addLeft(FUNC, SIN);
            diffTree->right->left->attachRight(Copy(tree->right));
        diffTree->right->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffLog(const Node *tree)
{
    assert(tree->right && !tree->left);

    Node* diffTree = new Node(FUNC, DEL);

    diffTree->attachLeft(Diff(tree->right));
    diffTree->attachRight(Copy(tree->left));

    return diffTree;
}

Node* Differentiator::DiffVar(const Node *tree)
{
    assert(tree->flag == VAR);

    Node* diffTree = nullptr;

    switch (tree->value)
    {

        case X_VAR:
            diffTree = new Node(NUM, 1);
            break;
        case Y_VAR:
            diffTree = new Node(NUM, 0);
            break;

        default:
            diffTree = nullptr;
    }

    return diffTree;
}

Node* Differentiator::DiffNum()
{
    Node* diffTree = new Node(NUM, 0);

    return diffTree;
}

Node* Differentiator::Copy(const Node *tree)
{
    Node* newNode = new Node(tree->flag, tree->value);

    if (tree->left)
        newNode->attachLeft(Copy(tree->left));

    if (tree->right)
        newNode->attachRight(Copy(tree->right));

    return newNode;
}
