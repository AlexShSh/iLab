#include <iostream>
#include "RDParser.h"

RDParser::RDParser(char* string):
        str(string) {}

Node* RDParser::CreateNode()
{
    return GetG();
}

Node* RDParser::GetG()
{
    Node* val = GetE();
    if (*str != '\0')
        printf("String isn't null-terminated : %s\n", str);

    return val;
}

Node* RDParser::GetN()
{

    if ((*str == 'x' || *str == 'y') && ('a' >= str[1] || str[1] >= 'z'))
    {
        if (*str == 'x')
        {
            Step();
            Node* node = new Node(VAR, X_VAR);
            return node;
        }
        else
        {
            Step();
            Node* node = new Node(VAR, Y_VAR);
            return node;
        }
    }

    int val = 0;
    bool ifWlile = false;

    while ('0' <= *str && *str <= '9')
    {
        ifWlile = true;
        val = val * 10 + *str - '0';
        Step();
    }
    if (!ifWlile)
        printf("Syntax error N: %s\n", str);

    Node* node = new Node(NUM, val);
    return node;
}

Node* RDParser::GetE()
{
    Node* root = GetT();

    while (*str == '+' || *str == '-')
    {
        if (*str == '+')
        {
            Step();
            Node* lchild = root;
            root = new Node(FUNC, SUM);
            root->attachLeft(lchild);
            root->attachRight(GetT());
        }

        else
        {
            Step();
            Node* lchild = root;
            root = new Node(FUNC, SUB);
            root->attachLeft(lchild);
            root->attachRight(GetT());
        }

    }
    return root;
}

Node* RDParser::GetT()
{
    Node* root = GetP();

    while (*str == '*' || *str == '/')
    {
        if (*str == '*')
        {
            Step();
            Node* lchild = root;
            root = new Node(FUNC, MUL);
            root->attachLeft(lchild);
            root->attachRight(GetP());
        }

        else
        {
            Step();
            Node* lchild = root;
            root = new Node(FUNC, DEL);
            root->attachLeft(lchild);
            root->attachRight(GetP());
        }

    }
    return root;
}

Node* RDParser::GetP()
{
    if (*str == '(')
    {
        Step();
        Node* root = GetE();
        if (*str != ')')
            printf("Syntax error P1: %s\n", str);
        Step();
        return root;
    }
    else if ('a' <= *str && *str <= 'z' && 'a' <= str[1] && str[1] <= 'z')
    {
        return GetF();
    }
    else
    {
        return GetN();
    }
}

Node* RDParser::GetF()
{
    if (*str == 's' && str[1] == 'i' && str[2] == 'n' && str[3] == '(')
    {
        Step(4);
        Node* root = new Node(FUNC, SIN);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 'c' && str[1] == 'o' && str[2] == 's' && str[3] == '(')
    {
        Step(4);
        Node* root = new Node(FUNC, COS);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 't' && str[1] == 'a' && str[2] == 'n' && str[3] == '(')
    {
        Step(4);
        Node* root = new Node(FUNC, TAN);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 'c' && str[1] == 'o' && str[2] == 't' && str[3] == '(')
    {
        Step(4);
        Node* root = new Node(FUNC, COT);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 'l' && str[1] == 'n' &&  str[2] == '(')
    {
        Step(3);
        Node* root = new Node(FUNC, LOG);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 'e' && str[1] == 'x' && str[2] == 'p' && str[3] == '(')
    {
        Step(4);
        Node* root = new Node(FUNC, EXP);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else if (*str == 's' && str[1] == 'q' && str[2] == 'r' && str[3] == 't' && str[4] == 't')
    {
        Step(5);
        Node* root = new Node(FUNC, SQRT);
        root->attachRight(GetE());
        if (*str != ')')
        {
            printf("Syntax Error F: %s", str);
        }
        Step();
        return root;
    }
    else
    {
        printf("Error unknown func: %s", str);
        return nullptr;
    }
}


void RDParser::Step()
{
    str++;
    while (*str == ' ')
        str++;
}

void RDParser::Step(size_t step)
{
    str += step;
    while (*str == ' ')
        str++;
}