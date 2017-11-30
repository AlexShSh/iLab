#pragma once

typedef int value_t;

typedef struct Node
{
    struct Node* left;
    struct Node* right;
    value_t value;
} Node;


Node* CreateNode(value_t val);
void AddLeftNode(Node* root, value_t val);
void AddRightNode(Node* root, value_t val);
void DeleteSubtree(Node* root);
void NodeDot(Node* root);
void NodeFprintf(FILE* fdot, Node* root, char* str);
