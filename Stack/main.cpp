#include <iostream>
#include "Stack.h"

int SolveLinear(int a, int b);
int SolveFormula(int a, int b, int c);

int main()
{
    int a = 0, b = 0, c = 0;
    printf("Linear equation: ax + b = 0\n"
                   "Enter a and b\n"
                   "a = ");
    scanf("%d", &a);
    printf("\nb = ");
    scanf("%d", &b);
    printf("x = %d", SolveLinear(a, b));


    printf("a = ");
    scanf("%d", &a);
    printf("b = ");
    scanf("%d", &b);
    printf("c = ");
    scanf("%d", &c);
    printf("4a - 3c^3 + abc + 4 = %d", SolveFormula(a, b, c));

    return 0;
}

int SolveLinear(int a, int b)
{
    auto stk = new Stack();

    // x = 0 - b/a --> 0 b a / -

    stk->Push(0);
    stk->Push(b);
    stk->Push(a);
    stk->Div();
    stk->Sub();

    int res = stk->Pop();;
    delete stk;

    return res;
}

int SolveFormula(int a, int b, int c)
{
    auto stk = new Stack();

    //4a - 3c^3 + abc + 4 -->  4 a * 3 c 3 ^ * - a b c * * + 4 +

    stk->Push(4);
    stk->Push(a);
    stk->Mul();
    stk->Push(3);
    stk->Push(c);
    stk->Push(3);
    stk->Pow();
    stk->Mul();
    stk->Sub();
    stk->Push(a);
    stk->Push(b);
    stk->Push(c);
    stk->Mul();
    stk->Mul();
    stk->Add();
    stk->Push(4);
    stk->Add();


    int res = stk->Pop();
    delete stk;

    return res;
}