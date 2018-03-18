#ifndef NODECLASS_NODE_H
#define NODECLASS_NODE_H

#include <cassert>
#include <cstdlib>
#include <cstdio>


enum FLAG
{
    NUM = 1,
    VAR,
    FUNC
};

enum
{
    SUM = 10,
    SUB,
    MUL,
    DEL,
    SIN,
    COS,
    LOG,
    TAN,
    COT,
    SQRT,
    EXP,

    X_VAR = 30,
    Y_VAR
};


typedef int value_t;

class Node
{
public:
    Node* left;
    Node* right;
    Node* parent;
    value_t value;
    FLAG flag;

    Node();
    Node(FLAG flag, value_t val);

    void addLeft(FLAG flag, value_t val);
    void addRight(FLAG flag, value_t val);

    void attachLeft(Node* l);
    void attachRight(Node* r);

    bool IsLeftChild();
    bool IsRightChild();

    void Dot(const char* filename);

    ~Node();
private:
    void fprintDot(FILE *fdot);
    const char* val2str();
};

#endif //NODECLASS_NODE_H
