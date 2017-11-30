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
    Node* root = CreateNode(num);
    scanf("%d", &num);

    while (num != END_NUM)
    {
        AddNodeSort(root, num);
        scanf("%d", &num);
    }
    PrintNodeSort(root);
    NodeDot(root);

    return 0;
}


void AddNodeSort(Node* root, value_t val)
{
    assert(root);

    if (val >= root->value)
    {
        if (!root->right)
            AddRightNode(root, val);
        else
            AddNodeSort(root->right, val);
    }
    else // val < root->value;
    {
        if (!root->left)
            AddLeftNode(root, val);
        else
            AddNodeSort(root->left, val);
    }
}


void PrintNodeSort(Node* root)
{
    assert(root);

    if (root->left)
        PrintNodeSort(root->left);

    printf("%d ", root->value);

    if (root->right)
        PrintNodeSort(root->right);
}