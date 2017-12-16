#pragma once

typedef char* value_t;

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    value_t value;
} Node;


Node* nodeCreate(value_t value);
value_t nodeAddValue(value_t value);
void nodeAddLeft(Node* root, value_t value);
void nodeAddRight(Node* root, value_t value);
void nodeDelete(Node* root);
void nodeDot(Node* root);
void nodeFprintDot(FILE* fdot, Node *root, const char *str);
void nodeFprint(FILE* fout, Node* node);
