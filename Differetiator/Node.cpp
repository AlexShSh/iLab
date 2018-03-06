#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Node.h"


Node::Node()
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    flag = NUM;
    value = 0;
}

Node::Node(FLAG fl, value_t val)
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    flag = fl;
    value = val;
}

void Node::addLeft(FLAG fl, value_t val)
{
    if (left)
        delete left;

    left = new Node(fl, val);
    left->parent = this;
}

void Node::addRight(FLAG fl, value_t val)
{
    if (right)
        delete right;

    right = new Node(fl, val);
    right->parent = this;
}

void Node::attachLeft(Node* l)
{
    if (left)
        delete left;

    left = l;
    left->parent = this;
}

void Node::attachRight(Node* r)
{
    if (right)
        delete right;

    right = r;
    right->parent = this;
}

void Node::Dot(const char* filename)
{
    FILE* fdot = fopen(filename, "w");
    assert(fdot && "Failed to open file");

    fprintf(fdot, "digraph G {\n"
            "node[shape=\"box\", color=\"DarkGreen\", fillcolor=\"green\", style=\"rounded,filled\", "
            "penwidth=2, label=\" \", fontsize=18, fontcolor=\"Maroon\"]\n"
            "edge[color=\"SaddleBrown\", fontsize=16, fontcolor=\"Maroon\"];\n");
    this->fprintDot(fdot);
    fprintf(fdot, "}\n");

    fclose(fdot);
}

void Node::fprintDot(FILE *fdot)
{
    assert(fdot && "File is nullptr");

    if (flag == NUM)
        fprintf(fdot, "El_%x [label=\"%d\"];\n", this, value);
    else
        fprintf(fdot, "El_%x [label=\"%s\"];\n", this, val2str());

    if (left)
    {
        fprintf(fdot, "El_%x -> El_%x;\n", this, left);
        left->fprintDot(fdot);
    }

    if (right)
    {
        fprintf(fdot, "El_%x -> El_%x;\n", this, right);
        right->fprintDot(fdot);
    }
}

const char* Node::val2str()
{
    switch (value)
    {
        case SUM:
            return "+";
        case SUB:
            return "-";
        case MUL:
            return "*";
        case DEL:
            return "/";
        case SIN:
            return "sin";
        case COS:
            return "cos";
        case LOG:
            return "ln";

        case X_VAR:
            return "x";
        case Y_VAR:
            return "y";

        default:
            return "Unknown";
    }

}

Node::~Node()
{
    if (left)
    {
        delete left;
        left = nullptr;
    }
    if (right)
    {
        delete right;
        right = nullptr;
    }
}
