#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Node.h"


Node* nodeCreate(value_type value)
{
    Node* NewNode = (Node*) calloc(1, sizeof(Node));
    assert(NewNode && "Failed to create new node");

    NewNode->left = NULL;
    NewNode->right = NULL;
    NewNode->parent = NULL;
    if (value)
        NewNode->value = nodeAddValue(value);
    else
        NewNode->value = NULL;

    return NewNode;
}


value_type nodeAddValue(value_type value)
{
    assert(value && "Char pointer is NULL");

    size_t len = strlen(value) + 1;

    char* buf = (char*) calloc(len, sizeof(char));
    assert(buf && "Failed to create buf");

    memcpy(buf, value, sizeof(char) * len);

    return buf;
}


void nodeAddLeft(Node* root, value_type value)
{
    assert(root && "Root is NULL");

    Node* left = nodeCreate(value);
    if (root->left)
        nodeDelete(root->left);
    left->parent = root;
    root->left = left;
}


void nodeAddRight(Node* root, value_type value)
{
    assert(root && "Root is NULL");

    Node* right = nodeCreate(value);
    if (root->right)
        nodeDelete(root->right);
    right->parent = root;
    root->right = right;
}


void nodeDelete(Node* root)
{
    assert(root && "Root is NULL");

    if (root->left)
        nodeDelete(root->left);
    if (root->right)
        nodeDelete(root->right);

    if (root->value)
        free(root->value);

    free(root);
}


void nodeDot(Node* root)
{
    assert(root && "Root is NULL");

    FILE* fdot = fopen("Node.dot", "w");
    assert(fdot && "Failed to open file");

    fprintf(fdot, "digraph G {\n"
            "node[shape=\"box\", color=\"DarkGreen\", fillcolor=\"green\", style=\"rounded,filled\", "
            "penwidth=2, label=\" \", fontsize=18, fontcolor=\"Maroon\"];\n");
    nodeFprintDot(fdot, root, "");
    fprintf(fdot, "}\n");

    fclose(fdot);
}

void nodeFprintDot(FILE *fdot, Node *root, const char *str)
{
    assert(root && "Root is NULL");
    assert(fdot && "File is NULL");

    fprintf(fdot, "El_%x [label=\"%s\"];\n",(unsigned int) root, root->value); //, xlabel="%s"  str
    if (root->left)
    {
        fprintf(fdot, "El_%x -> El_%x [color=\"SaddleBrown\", label=\"yes\", fontsize=16, fontcolor=\"Maroon\"];\n",(unsigned int) root,(unsigned int) root->left);
        nodeFprintDot(fdot, root->left, "yes");
    }

    if (root->right)
    {
        fprintf(fdot, "El_%x -> El_%x [color=\"SaddleBrown\", label=\"no\", fontsize=16, fontcolor=\"Maroon\"];\n",(unsigned int) root,(unsigned int) root->right);
        nodeFprintDot(fdot, root->right, "no");
    }
}


void nodeFprint(FILE* fout, Node* node)
{
    assert(fout && "File pointer is NULL");
    assert(node && "Node pointer is NULL");

    fprintf(fout, "{ \"%s~ ", node->value);

    if (node->left)
        nodeFprint(fout, node->left);

    if (node->right)
        nodeFprint(fout, node->right);

    fprintf(fout, "} ");

}


Node* nodeFind(Node* root, char* str)
{
    if (strcmp(root->value, str) == 0)
        return root;

    Node* res = NULL;

    if (root->left)
        res = nodeFind(root->left, str);
    if (res)
        return res;

    if (root->right)
        res = nodeFind(root->right, str);
    if (res)
        return res;

    return NULL;
}
