#ifndef DIFFERENTIATOR_RDPARSER_H
#define DIFFERENTIATOR_RDPARSER_H

#include "Node.h"

class RDParser
{
    char* str;

public:
    RDParser(char* string);
    Node* CreateNode();

private:
    Node*  GetG();
    Node*  GetE();
    Node*  GetT();
    Node*  GetP();
    Node*  GetN();
    Node*  GetF();

    void Step();
    void Step(size_t step);
};


#endif //DIFFERENTIATOR_RDPARSER_H
