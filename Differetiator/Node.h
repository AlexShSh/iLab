//
// Created by alex on 27.02.18.
//

#include <cassert>
#include <cstdlib>
#include <cstdio>

#ifndef NODECLASS_NODE_H
#define NODECLASS_NODE_H


enum FLAG
{
    NUM = 0,
    VAR,
    FUNC
};

enum
{
    SUM = 10,
    SUB,
    MUL,
    DEL,

    X_VAR = 20
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

    void Dot();
    void fprintDot(FILE *fdot);

    ~Node();
};


#endif //NODECLASS_NODE_H
