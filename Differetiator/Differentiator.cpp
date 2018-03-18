#include <cstdio>
#include <cassert>
#include "Differentiator.h"


Differentiator::Differentiator(FILE *f):
     TexOut(TexOutput(f)) {}

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
            diffTree = DiffNum(tree);
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
        case TAN:
            diffTree = DiffTan(tree);
            break;
        case COT:
            diffTree = DiffCot(tree);
            break;
        case SQRT:
            diffTree = DiffSqrt(tree);
            break;
        case EXP:
            diffTree = DiffExp(tree);
            break;

        default:
            diffTree = nullptr;
    }

    return diffTree;
}

Node* Differentiator::DiffSum(const Node *tree)
{
    assert(tree->left && tree->right);

    TexOut.difSum(tree);

    Node* diffTree = new Node(FUNC, SUM);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffSub(const Node *tree)
{
    assert(tree->left && tree->right);

    TexOut.difSub(tree);

    Node* diffTree = new Node(FUNC, SUB);

    diffTree->attachLeft(Diff(tree->left));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffMul(const Node *tree)
{
    assert(tree->left && tree->right);

    TexOut.difMul(tree);

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

    TexOut.difDel(tree);

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

    TexOut.difSin(tree);

    Node* diffTree = new Node(FUNC, MUL);

    diffTree->addLeft(FUNC, COS);
    diffTree->left->attachRight(Copy(tree->right));

    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffCos(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difCos(tree);

    Node* diffTree = new Node(FUNC, MUL);

    diffTree->addLeft(NUM, -1);
    diffTree->addRight(FUNC, MUL);
    diffTree->right->addLeft(FUNC, SIN);
    diffTree->right->left->attachRight(Copy(tree->right));
    diffTree->right->attachRight(Diff(tree->right));

    return diffTree;
}

Node* Differentiator::DiffLog(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difLog(tree);

    Node* diffTree = new Node(FUNC, DEL);

    diffTree->attachLeft(Diff(tree->right));
    diffTree->attachRight(Copy(tree->right));

    return diffTree;
}


Node* Differentiator::DiffTan(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difTan(tree);

    Node* diffTree = new Node(FUNC, DEL);

    diffTree->attachLeft(Diff(tree->right));
    diffTree->addRight(FUNC, MUL);
        diffTree->right->addLeft(FUNC, COS);
            diffTree->right->left->attachRight(Copy(tree->right));
        diffTree->right->addRight(FUNC, COS);
            diffTree->right->right->attachRight(Copy(tree->right));

    return diffTree;
}


Node* Differentiator::DiffCot(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difCot(tree);

    Node* diffTree = new Node(FUNC, DEL);

    diffTree->addLeft(FUNC, MUL);
        diffTree->left->addLeft(NUM, -1);
        diffTree->left->attachRight(Diff(tree->right));
    diffTree->addRight(FUNC, MUL);
        diffTree->right->addLeft(FUNC, SIN);
            diffTree->right->left->attachRight(Copy(tree->right));
        diffTree->right->addRight(FUNC, SIN);
            diffTree->right->right->attachRight(Copy(tree->right));

    return diffTree;
}


Node* Differentiator::DiffSqrt(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difSqrt(tree);

    Node* diffTree = new Node(FUNC, DEL);

    diffTree->attachLeft(Diff(tree->right));
    diffTree->addRight(FUNC, MUL);
        diffTree->right->addLeft(NUM, 2);
        diffTree->right->attachRight(Copy(tree));

    return diffTree;
}

Node* Differentiator::DiffExp(const Node *tree)
{
    assert(tree->right && !tree->left);

    TexOut.difExp(tree);

    Node* diffTree = new Node(FUNC, MUL);

    diffTree->attachLeft(Copy(tree));
    diffTree->attachRight(Diff(tree->right));

    return diffTree;
}


///////
Node* Differentiator::DiffVar(const Node *tree)
{
    assert(tree->flag == VAR);

    Node* diffTree = nullptr;

    switch (tree->value)
    {

        case X_VAR:
            diffTree = new Node(NUM, 1);
            TexOut.difVarX(tree);
            break;
        case Y_VAR:
            diffTree = new Node(NUM, 0);
            TexOut.difVarY(tree);
            break;

        default:
            diffTree = nullptr;
    }

    return diffTree;
}

Node* Differentiator::DiffNum(const Node* tree)
{
    Node* diffTree = new Node(NUM, 0);
    TexOut.difNum(tree);

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
