#ifndef NODECLASS_TEXOUTPUT_H
#define NODECLASS_TEXOUTPUT_H

#include <iostream>
#include "Node.h"

class TexOutput
{
public:

    TexOutput(FILE* f);
    void printPreambula();
    void printEnd();
    void printTree(const Node* tree);
    void printNode(const Node* tree);
private:
    FILE* fout;
    void printVar(const Node* tree);
    void printFunc(const Node* tree);

public:
    void difSum(const Node *node);
    void difSub(const Node *node);
    void difMul(const Node *node);
    void difDel(const Node *node);
    void difSin(const Node *node);
    void difCos(const Node *node);
    void difLog(const Node *node);
    void difTan(const Node *node);
    void difCot(const Node *node);
    void difSqrt(const Node *node);
    void difExp(const Node *node);

    void difNum(const Node* node);
    void difVarX(const Node* node);
    void difVarY(const Node* node);

    void optConstSum(const Node* node);
    void optConstSub(const Node* node);
    void optConstMul(const Node* node);

    void opt0pl(const Node* node);
    void optPl0(const Node* node);
    void opt1ml(const Node* node);
    void optMl1(const Node* node);
    void opt0ml(const Node* node);
    void optMl0(const Node* node);
    void optSb0(const Node* node);
    void opt0sb(const Node* node);
    void opt0del(const Node* node);
};


#endif //NODECLASS_TEXOUTPUT_H
