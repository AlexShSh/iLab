//
// Created by alex on 27.02.18.
//

#include <cstdio>
#include "Node.h"

Node::Node()
{
    left = NULL;
    right = NULL;
    parent = NULL;
    flag = NUM;
    value = 0;
}

Node::Node(FLAG fl, value_t val)
{
    left = NULL;
    right = NULL;
    parent = NULL;
    flag = fl;
    value = val;
}

void Node::addLeft(FLAG fl, value_t val)
{
    left = new Node(fl, val);
    left->parent = this;
}

void Node::addRight(FLAG fl, value_t val)
{
    right = new Node(fl, val);
    right->parent = this;
}

void Node::attachLeft(Node* l)
{
    left = l;
    left->parent = this;
}

void Node::attachRight(Node* r)
{
    right = r;
    right->parent = this;
}

void Node::Dot()
{
    FILE* fdot = fopen("Node.dot", "w");
    assert(fdot && "Failed to open file");

    fprintf(fdot, "digraph G {\n"
            "node[shape=\"box\", color=\"DarkGreen\", fillcolor=\"green\", style=\"rounded,filled\", "
            "penwidth=2, label=\" \", fontsize=18, fontcolor=\"Maroon\"];\n");
    this->fprintDot(fdot);
    fprintf(fdot, "}\n");

    fclose(fdot);
}

void Node::fprintDot(FILE *fdot)
{
    assert(fdot && "File is nullptr");

    fprintf(fdot, "El_%x [label=\"%d; %d\"];\n", this, flag, value);
    if (left)
    {
        fprintf(fdot, "El_%x -> El_%x [color=\"SaddleBrown\", fontsize=16, fontcolor=\"Maroon\"];\n", this, left);
        left->fprintDot(fdot);
    }

    if (right)
    {
        fprintf(fdot, "El_%x -> El_%x [color=\"SaddleBrown\", fontsize=16, fontcolor=\"Maroon\"];\n", this, right);
        right->fprintDot(fdot);
    }
}

Node::~Node()
{
    if (left)
    {
        left->~Node();
        left = NULL;
    }
    if (right)
    {
        right->~Node();
        right = NULL;
    }

    delete this;
}