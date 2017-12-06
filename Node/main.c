#include <stdio.h>
#include <assert.h>
#include "Node_header.h"

#define END_NUM (-666)

void AddNodeSort(Node* root, value_t val);
void PrintNodeSort(Node* root);


int main()
{
    printf("Enter several numbers; to finish, enter -666\n");
    int num  = 0;
    scanf("%d", &num);
    Node* root = nodeCreate(num);
    scanf("%d", &num);

    while (num != END_NUM)
    {
        AddNodeSort(root, num);
        scanf("%d", &num);
    }
    PrintNodeSort(root);
    nodeDot(root);

    return 0;
}


void AddNodeSort(Node* root, value_t val)
{
    assert(root && "Root is NULL");

    if (val >= root->value)
    {
        if (!root->right)
            nodeAddRight(root, val);
        else
            AddNodeSort(root->right, val);
    }
    else // val < root->value;
    {
        if (!root->left)
            nodeAddLeft(root, val);
        else
            AddNodeSort(root->left, val);
    }
}


void PrintNodeSort(Node* root)
{
    assert(root && "Root is NULL");

    if (root->left)
        PrintNodeSort(root->left);

    printf("%d ", root->value);

    if (root->right)
        PrintNodeSort(root->right);
}
