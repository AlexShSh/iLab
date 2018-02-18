#pragma once

typedef char* value_type;

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    value_type value;
} Node;


Node* nodeCreate(value_type value);
value_type nodeAddValue(value_type value);
void nodeAddLeft(Node* root, value_type value);
void nodeAddRight(Node* root, value_type value);
void nodeDelete(Node* root);
void nodeDot(Node* root);
void nodeFprintDot(FILE* fdot, Node *root, const char *str);
void nodeFprint(FILE* fout, Node* node);
Node* nodeFind(Node* root, char* str);
