#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Node_header.h"

Node* nodeCreate(value_t val)
{
    Node* NewNode = (Node*) calloc(1, sizeof(Node));
    assert(NewNode && "Failed to create new node");

    NewNode->left = NULL;
    NewNode->right = NULL;
    NewNode->value = val;

    return NewNode;
}

void nodeAddLeft(Node* root, value_t val)
{
    assert(root && "Root is NULL");

    Node* left = nodeCreate(val);
    if (root->left)
        nodeDeleteSubtree(root->left);
    root->left = left;
}

void nodeAddRight(Node* root, value_t val)
{
    assert(root && "Root is NULL");

    Node* right = nodeCreate(val);
    if (root->right)
        nodeDeleteSubtree(root->right);
    root->right = right;
}

void nodeDeleteSubtree(Node* root)
{
    assert(root && "Root is NULL");

    if (root->left)
        nodeDeleteSubtree(root->left);
    if (root->right)
        nodeDeleteSubtree(root->right);

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
    nodeFprint(fdot, root, "Root");
    fprintf(fdot, "}\n");

    fclose(fdot);
}

void nodeFprint(FILE* fdot, Node* root, const char* str)
{
    assert(root && "Root is NULL");
    assert(fdot && "File is NULL");

    fprintf(fdot, "El%d [label=\"%d\", xlabel=\"%s\"];\n",(int) root, root->value, str);
    if (root->left)
    {
        fprintf(fdot, "El%d -> El%d [color=\"SaddleBrown\"];\n",(int) root,(int) root->left);
        nodeFprint(fdot, root->left, "L");
    }

    if (root->right)
    {
        fprintf(fdot, "El%d -> El%d [color=\"SaddleBrown\"];\n",(int) root,(int) root->right);
        nodeFprint(fdot, root->right, "R");
    }
}
