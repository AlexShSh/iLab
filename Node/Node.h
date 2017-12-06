#pragma once

typedef int value_t;

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    value_t value;
} Node;


Node* nodeCreate(value_t val);
void nodeAddLeft(Node* root, value_t val);
void nodeAddRight(Node* root, value_t val);
void nodeDeleteSubtree(Node* root);
void nodeDot(Node* root);
void nodeFprint(FILE* fdot, Node* root, const char* str);
