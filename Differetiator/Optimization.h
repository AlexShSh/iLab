#ifndef NODECLASS_OPTIMIZATION_H
#define NODECLASS_OPTIMIZATION_H

#include <iostream>
#include "Node.h"
#include "TexOutput.h"

class Optimization
{
private:
    TexOutput TexOut;
public:
    Optimization(FILE* f);
    void Optimize(Node** nodeptr);

private:
    void OptCut(Node** node);
    void ConvConst(Node* node);

    void CutSum(Node** node);
    void CutSub(Node** node);
    void CutMul(Node** node);
    void CutDel(Node** node);

    void CutLeft(Node** node);
    void CutRight(Node** node);

};


#endif //NODECLASS_OPTIMIZATION_H
