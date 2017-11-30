#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Node_header.h"

Node* CreateNode(value_t val)
{
    Node* NewNode = (Node*) calloc(1, sizeof(Node));
    assert(NewNode);
    NewNode->left = NULL;
    NewNode->right = NULL;
    NewNode->value = val;

    return NewNode;
}

void AddLeftNode(Node* root, value_t val)
{
    assert(root);
    Node* left = CreateNode(val);
    if (root->left)
        DeleteSubtree(root->left);
    root->left = left;
}

void AddRightNode(Node* root, value_t val)
{
    assert(root);
    Node* right = CreateNode(val);
    if (root->right)
        DeleteSubtree(root->right);
    root->right = right;
}

void DeleteSubtree(Node* root)
{
    assert(root);
    if (root->left)
        DeleteSubtree(root->left);
    if (root->right)
        DeleteSubtree(root->right);
    free(root);
}


void NodeDot(Node* root)
{
    assert(root);

    FILE* fdot = fopen("Node.dot", "w");
    assert(fdot);

    fprintf(fdot, "digraph G {\n"
                  "node[shape=\"box\", color=\"DarkGreen\", fillcolor=\"green\", style=\"rounded,filled\", "
                  "penwidth=2, label=\" \", fontsize=18, fontcolor=\"Maroon\"];\n");
    NodeFprintf(fdot, root, "Root");
    fprintf(fdot, "}\n");

    fclose(fdot);

    system("Dot-comand.bat");
}

void NodeFprintf(FILE* fdot, Node* root, char* str)
{
    fprintf(fdot, "El%d [label=\"%d\", xlabel=\"%s\"];\n",(int) root, root->value, str);
    if (root->left)
    {
        fprintf(fdot, "El%d -> El%d [color=\"SaddleBrown\"];\n",(int) root,(int) root->left);
        NodeFprintf(fdot, root->left, "L");
    }

    if (root->right)
    {
        fprintf(fdot, "El%d -> El%d [color=\"SaddleBrown\"];\n",(int) root,(int) root->right);
        NodeFprintf(fdot, root->right, "R");
    }
}
