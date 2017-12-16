#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Akinator.h"
#include "Node.h"


char* CreateBuffer()
{
    FILE *fin = fopen("akinator-lib.txt", "r");
    assert(fin && "Faile to open file");

    fseek(fin, 0, SEEK_END);
    size_t bufSize = (size_t) ftell(fin) + 1;
    fseek(fin, 0, SEEK_SET);

    char* buffer = (char*) calloc(bufSize , sizeof(char));
    assert(buffer && "Failed to create buffer");

    fread(buffer, sizeof(char), bufSize, fin);

    fclose(fin);

    return buffer;
}


Node* CreateAkinatorTree()
{
    char *buf = CreateBuffer();
    char *cur = buf;

    Node* tree = nodeCreate(NULL);

    while (*cur != '{')
        cur++;

    cur++;
    cur = AddAkinatorTree(tree, cur);

    if (*cur == '\0')
    {
        free(buf);
        return tree;
    }
    else
    {
        nodeDelete(tree);
        free(buf);
        return NULL;
    }
}


char* AddAkinatorTree(Node* node, char* cur)
{
    assert(node && "Node pointer is NULL");
    assert(cur && "Char pointer is NULL");

    while (*cur != '"')
        cur++;

    cur++;
    char* begStr = cur;
    while (*cur != '~')
        cur++;
    *cur = '\0';
    cur++;

    node->value = nodeAddValue(begStr);

    SKIP_SPASES;

    if (*cur == '{')
    {
        nodeAddLeft(node, NULL);
        cur = AddAkinatorTree(node->left, cur);
        while (*cur != '{')
            cur++;

        nodeAddRight(node, NULL);
        cur = AddAkinatorTree(node->right, cur);
        SKIP_SPASES;
    }

    cur++;
    SKIP_SPASES;

    return cur;
}


void WriteAkinatorTree(Node* tree)
{
    FILE* fout = fopen("akinator-lib.txt", "w");
    assert(fout && "Faile to open file");

    nodeFprint(fout, tree);

    fclose(fout);
}


void Akinator(Node* tree)
{
    const char* PositiveAnswer = "yes";
    const char* NegativeAnswer = "no";

    Node* node = tree;
    char* answ_buf = (char*) calloc(ANSW_BUFF_SIZE + 1, sizeof(char));

    while (node->left)    // children exist
    {
        AskQuestion(node);
        GetAnswer(answ_buf);

        if (strcmp(answ_buf, PositiveAnswer) == 0)
        {
            node = node->left;
        }
        else if (strcmp(answ_buf, NegativeAnswer) == 0)
        {
            node = node->right;
        }
        else
        {
            printf("I don't understand!\n");
        }
        ClearBuffer(answ_buf);
    }

    AskQuestion(node);
    GetAnswer(answ_buf);
    while (strcmp(answ_buf, NegativeAnswer) != 0 && strcmp(answ_buf, PositiveAnswer) != 0)
    {
        printf("I don't understand!\n");
        ClearBuffer(answ_buf);
        GetAnswer(answ_buf);
    }

    if (strcmp(answ_buf, PositiveAnswer) == 0)
    {
        printf("I'm a genius!\n");
    }
    else
    {
        printf("Who is it?\n");
        GetAnswer(answ_buf);

        nodeAddLeft(node, answ_buf);
        ClearBuffer(answ_buf);

        nodeAddRight(node, node->value);

        printf("Than %s differs from %s?\n", node->left->value, node->right->value);
        GetAnswer(answ_buf);

        free(node->value);
        node->value = nodeAddValue(answ_buf);
    }

    free(answ_buf);
}


void AskQuestion(Node* node)
{
    printf("%s?\n", node->value);
}


void GetAnswer(char* answ_buf)
{
    fgets(answ_buf, ANSW_BUFF_SIZE, stdin);
    if (answ_buf[strlen(answ_buf) - 1] == '\n')
        answ_buf[strlen(answ_buf) - 1] = '\0';
}


void ClearBuffer(char* buf)
{
    while (*buf != '\0')
    {
        *buf = '\0';
        buf++;
    }
}
