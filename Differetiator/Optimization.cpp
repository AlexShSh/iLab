#include "Optimization.h"

bool NEED_OPT = true;


Optimization::Optimization(FILE *f):
    TexOut(TexOutput(f)){}

void Optimization::Optimize(Node** nodeptr)
{
    while (NEED_OPT)
    {
        NEED_OPT = false;
        ConvConst(*nodeptr);
        OptCut(nodeptr);
    }
}

void Optimization::ConvConst(Node* node)
{
    if (node->left)
        ConvConst(node->left);
    if (node->right)
        ConvConst(node->right);

    if (node->flag == FUNC && node->left && node->right && node->left->flag == NUM && node->right->flag == NUM)
    {
        int res = 0;

        switch (node->value)
        {
            case SUM:
                TexOut.optConstSum(node);
                res = node->left->value + node->right->value;
                break;
            case SUB:
                TexOut.optConstSub(node);
                res = node->left->value - node->right->value;
                break;
            case MUL:
                TexOut.optConstMul(node);
                res = node->left->value * node->right->value;
                break;
            default:
                break;
        }
        delete node->left;
        node->left = nullptr;
        delete node->right;
        node->right = nullptr;

        node->flag = NUM;
        node->value = res;

        NEED_OPT = true;
    }
}


void Optimization::OptCut(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->left)
        OptCut(&((*nodeptr)->left));
    if (node->right)
        OptCut(&((*nodeptr)->right));

    if (node->flag == FUNC)
    {
        switch (node->value)
        {
            case SUM:
                CutSum(nodeptr);
                break;
            case SUB:
                CutSub(nodeptr);
                break;
            case MUL:
                CutMul(nodeptr);
                break;
            case DEL:
                CutDel(nodeptr);
                break;
        }
    }
    if (*nodeptr == nullptr)
        (*nodeptr) = new Node(NUM, 0);
}

void Optimization::CutSum(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->left && node->left->flag == NUM && node->left->value == 0)
    {
        TexOut.opt0pl(node);
        CutLeft(nodeptr);
        NEED_OPT = true;
        return;
    }
    if (node->right && node->right->flag == NUM && node->right->value == 0)
    {
        TexOut.optPl0(node);
        CutRight(nodeptr);
        NEED_OPT = true;
        return;
    }
}


void Optimization::CutSub(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->right && node->right->flag == NUM && node->right->value == 0)
    {
        TexOut.optSb0(node);
        CutRight(nodeptr);
        NEED_OPT = true;
        return;
    }
    if (node->left && node->left->flag == NUM && node->left->value == 0)
    {
        TexOut.opt0sb(node);
        node->value = MUL;
        node->left->value = -1;
        NEED_OPT = true;
        return;
    }
}


void Optimization::CutMul(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->left && node->left->flag == NUM && node->left->value == 1)
    {
        TexOut.opt1ml(node);
        CutLeft(nodeptr);
        NEED_OPT = true;
        return;
    }

    if (node->right && node->right->flag == NUM && node->right->value == 1)
    {
        TexOut.optMl1(node);
        CutRight(nodeptr);
        NEED_OPT = true;
        return;
    }

    if (node->left && node->left->flag == NUM && node->left->value == 0 || node->right && node->right->flag == NUM && node->right->value == 0)
    {
        TexOut.opt0ml(node);
        if (node->IsLeftChild())
        {
            Node* par = node->parent;
            par->addLeft(NUM, 0);
        }
        else if (node->IsRightChild())
        {
            Node* par = node->parent;
            par->addRight(NUM, 0);
        }
        else
        {
            delete node;
            *nodeptr = nullptr;
        }

        NEED_OPT = true;
        return;
    }
}

void Optimization::CutDel(Node** nodeptr)
{
    Node* node = *nodeptr;



    if (node->left && node->left->flag == NUM && node->left->value == 0)
    {
        TexOut.opt0del(node);
        if (node->IsLeftChild())
        {
            Node* par = node->parent;
            par->addLeft(NUM, 0);
        }
        else if (node->IsRightChild())
        {
            Node* par = node->parent;
            par->addRight(NUM, 0);
        }
        else
        {
            delete node;
            *nodeptr = nullptr;
        }

        NEED_OPT = true;
        return;
    }
}


void Optimization::CutLeft(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->IsLeftChild())
    {
        node->right->parent = node->parent;
        node->parent->left =node->right;
        node->right = nullptr;
        delete node;
    }
    else if (node->IsRightChild())
    {
        node->right->parent = node->parent;
        node->parent->right = node->right;
        node->right = nullptr;
        delete node;
    }
    else
    {
        Node* tmp = *nodeptr;
        *nodeptr = (*nodeptr)->right;
        tmp->right = nullptr;
        delete tmp;
    }
}


void Optimization::CutRight(Node** nodeptr)
{
    Node* node = *nodeptr;
    if (node->IsLeftChild())
    {
        node->left->parent = node->parent;
        node->parent->left =node->left;
        node->left = nullptr;
        delete node;
    }
    else if (node->IsRightChild())
    {
        node->left->parent = node->parent;
        node->parent->right =node->left;
        node->left = nullptr;
        delete node;
    }
    else
    {
        Node* tmp = *nodeptr;
        *nodeptr = (*nodeptr)->left;
        tmp->left = nullptr;
        delete tmp;
    }
}