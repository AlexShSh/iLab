#include <iostream>
#include "TexOutput.h"

TexOutput::TexOutput(FILE* f):
        fout(f) {}

void TexOutput::printPreambula()
{
    fprintf(fout, "\\documentclass[12pt]{article}\n"
            "\\usepackage[utf8]{inputenc}\n"
            "\\usepackage[english, russian]{babel}\n"
            "\\usepackage{amsmath, amssymb, mathtools}\n"
            "\\usepackage[left = 20mm, bottom=15mm, top=15mm, right=10mm]{geometry}\n\n"
            "\\begin{document}\n");
}

void TexOutput::printEnd()
{
    fprintf(fout, "\\end{document}\n");
}

void TexOutput::printTree(const Node* tree)
{
    assert(tree && "Tree is nullptr!");

    fprintf(fout, "$ ");
    printNode(tree);
    fprintf(fout, "$\n\n");
}

void TexOutput::printNode(const Node* tree)
{
    assert(tree && "Tree is nullptr!");

    switch (tree->flag)
    {
        case NUM:
            fprintf(fout, "%d", tree->value);
            break;
        case VAR:
            printVar(tree);
            break;
        case FUNC:
            printFunc(tree);
            break;
    }
}

void TexOutput::printVar(const Node *tree)
{
    assert(tree && "Tree is nullptr!");

    switch (tree->value)
    {
        case X_VAR:
            fprintf(fout, "x");
            break;
        case Y_VAR:
            fprintf(fout, "y");
            break;
    }
}

void TexOutput::printFunc(const Node *tree)
{
    switch (tree->value)
    {
        case SUM:
            if (tree->parent)
                fprintf(fout, "(");
            printNode(tree->left);
            fprintf(fout, " + ");
            printNode(tree->right);
            if (tree->parent)
                fprintf(fout, ") ");
            break;
        case SUB:
            if (tree->parent)
                fprintf(fout, "(");
            printNode(tree->left);
            fprintf(fout, " - ");
            printNode(tree->right);
            if (tree->parent)
                fprintf(fout, ") ");
            break;
        case MUL:
            if (!(tree->left->flag == NUM && tree->left->value == 1))
            {
                if (tree->left->flag == NUM && tree->left->value == -1)
                    fprintf(fout, "-");
                else
                    printNode(tree->left);
            }
            if (!(tree->left->flag == NUM && tree->right->flag != NUM))
                fprintf(fout, "\\cdot ");
            printNode(tree->right);
            break;
        case DEL:
            fprintf(fout, "\\frac{");
            printNode(tree->left);
            fprintf(fout, "} {");
            printNode(tree->right);
            fprintf(fout, "} ");
            break;
        case LOG:
            fprintf(fout, "\\ln (");
            printNode(tree->right);
            fprintf(fout, ")");
            break;
        case SIN:
            fprintf(fout, "\\sin (");
            printNode(tree->right);
            fprintf(fout, ") ");
            break;
        case COS:
            fprintf(fout, "\\cos (");
            printNode(tree->right);
            fprintf(fout, ") ");
            break;
        case TAN:
            fprintf(fout, "\\tan (");
            printNode(tree->right);
            fprintf(fout, ") ");
            break;
        case COT:
            fprintf(fout, "\\cot (");
            printNode(tree->right);
            fprintf(fout, ") ");
            break;
        case SQRT:
            fprintf(fout, "\\sqrt{");
            printNode(tree->right);
            fprintf(fout, "}");
            break;
        case EXP:
            fprintf(fout, "e^{");
            printNode(tree->right);
            fprintf(fout, "}");
            break;
    }
}


void TexOutput::difSum(const Node *node)
{
    fprintf(fout, "Используя известный математический закон $(f + g)' = f' + g' $ получаем производную: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' = (");
    printNode(node->left);
    fprintf(fout, ")' + (");
    printNode(node->left);
    fprintf(fout, ")'$ \\\\ \n");
}

void TexOutput::difSub(const Node *node)
{
    fprintf(fout, "Десятиклассник знает, что $(f - g)' = f' - g' $. Используя это, получаем: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' = (");
    printNode(node->left);
    fprintf(fout, ")' - (");
    printNode(node->right);
    fprintf(fout, ")'$ \\\\ \n");
}

void TexOutput::difMul(const Node *node)
{
    fprintf(fout, "На 65 странице учебника Бесова доказано, что $(f \\cdot g)' = f'g + fg' $. Следовательно: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  (");
    printNode(node->left);
    fprintf(fout, ")' \\cdot (");
    printNode(node->right);
    fprintf(fout, ") + (");
    printNode(node->left);
    fprintf(fout, ") \\cdot (");
    printNode(node->right);
    fprintf(fout, ")'$ \\\\ \n ");
}

void TexOutput::difDel(const Node *node)
{
    fprintf(fout, "Г.Е. Иванов утверждает, что $(\\frac{f}{g})' = \\frac{f'g - fg'}{g^2} $. Поверив на слово, получим: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  \\frac{(");
    printNode(node->left);
    fprintf(fout, ")' \\cdot (");
    printNode(node->right);
    fprintf(fout, ") - (");
    printNode(node->left);
    fprintf(fout, ") \\cdot (");
    printNode(node->right);
    fprintf(fout, ")'}{(");
    printNode(node->right);
    fprintf(fout, ")^2}$ \\\\ \n ");
}

void TexOutput::difSin(const Node *node)
{
    fprintf(fout, "В учебнике Петровича написано: $(\\sin(f))' = \\cos(f) \\cdot f' $. Попробуем это применить: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  \\cos(");
    printNode(node->right);
    fprintf(fout, ") \\cdot (");
    printNode(node->right);
    fprintf(fout, ")' $ \\\\ \n");
}

void TexOutput::difCos(const Node *node)
{
    fprintf(fout, "Тер-Крикоров настаивает: $(\\cos(f))' = -\\sin(f) \\cdot f' $. Если это так, тогда: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  -\\sin(");
    printNode(node->right);
    fprintf(fout, ") \\cdot (");
    printNode(node->right);
    fprintf(fout, ")' $ \\\\ \n");
}

void TexOutput::difLog(const Node *node)
{
    fprintf(fout, "Все математики мира согласны, что: $(\\ln(f))' = \\frac{f'}{f} $. Согласимся и мы: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  \\frac{");
    printNode(node->right);
    fprintf(fout, "'}{");
    printNode(node->right);
    fprintf(fout, "} $ \\\\ \n");
}

void TexOutput::difTan(const Node *node)
{
    fprintf(fout, "Проснувшись на лекции, я узнал, что: $(\\tan(f))' = \\frac{f'}{\\cos^2(f)} $. Попробуем использовать: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  \\frac{(");
    printNode(node->right);
    fprintf(fout, ")'}{\\cos^2(");
    printNode(node->right);
    fprintf(fout, ")} $ \\\\ \n");
}

void TexOutput::difCot(const Node *node)
{
    fprintf(fout, "Интересный факт: $(\\сot(f))' = -\\frac{f'}{\\sin^2(f)} $. Как раз то, что нам нужно: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  -\\frac{(");
    printNode(node->right);
    fprintf(fout, ")'}{\\sin^2(");
    printNode(node->right);
    fprintf(fout, ")} $ \\\\ \n");
}

void TexOutput::difSqrt(const Node *node)
{
    fprintf(fout, "В тетрадке соседа написано: $(\\sqrt{f})' = \\frac{f'}{2\\sqrt{f}} $. Как раз то, что нам нужно: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  \\frac{");
    printNode(node->right);
    fprintf(fout, "'}{2\\sqrt{");
    printNode(node->right);
    fprintf(fout, "}} $ \\\\ \n");
}

void TexOutput::difExp(const Node *node)
{
    fprintf(fout, "Даже ежу известно: $((e^{f})' = e^{f} \\cdot f'$. Используем знания ежа: \\\\ \n $(");
    printNode(node);
    fprintf(fout, ")' =  e^{");
    printNode(node->right);
    fprintf(fout, "} \\cdot (");
    printNode(node->right);
    fprintf(fout, ")' $ \\\\ \n");
}


void TexOutput::difNum(const Node* node)
{
    fprintf(fout, "Из курса математического анализа известно, что $C' = 0$. Тогда: \\\\ \n $%d' = 0$ \\\\ \n", node->value);
}

void TexOutput::difVarX(const Node* node)
{
    fprintf(fout, "Применим великое математическое утверждение: $x' = 1$.  \\\\ \n");
}

void TexOutput::difVarY(const Node* node)
{
    fprintf(fout, "Как известно, при дифференцировании по $x$: $y' = 0$.  \\\\ \n");
}

void TexOutput::optConstSum(const Node* node)
{
    fprintf(fout, "Воспользуемся правилами сложения: $%d + %d = %d$ \\\\ \n", node->left->value, node->right->value, node->left->value + node->right->value);
}

void TexOutput::optConstSub(const Node* node)
{
    fprintf(fout, "Воспользуемся правилами вычитания: $%d - %d = %d$ \\\\ \n", node->left->value, node->right->value, node->left->value - node->right->value);
}

void TexOutput::optConstMul(const Node* node)
{
    fprintf(fout, "Воспользуемся правилами умножения: $%d \\cdot %d = %d$ \\\\ \n", node->left->value, node->right->value, node->left->value * node->right->value);
}

void TexOutput::opt0pl(const Node* node)
{
    fprintf(fout, "Математики думают, что $0 + ");
    printNode(node->right);
    fprintf(fout, " = ");
    printNode(node->right);
    fprintf(fout, "$ \\\\ \n ");
}

void TexOutput::optPl0(const Node* node)
{
    fprintf(fout, "Без сомнения: $ ");
    printNode(node->right);
    fprintf(fout, " + 0 = ");
    printNode(node->right);
    fprintf(fout, "$ \\\\ \n ");
}

void TexOutput::opt1ml(const Node* node)
{
    fprintf(fout, "Ходят слухи, что $ 1 \\cdot");
    printNode(node->right);
    fprintf(fout, " = ");
    printNode(node->right);
    fprintf(fout, "$ \\\\ \n ");
}

void TexOutput::optMl1(const Node* node)
{
    fprintf(fout, "Даже гуманитарий знает, что: $ ");
    printNode(node->left);
    fprintf(fout, " \\cdot 1 = ");
    printNode(node->left);
    fprintf(fout, "$ \\\\ \n ");
}

void TexOutput::opt0ml(const Node* node)
{
    fprintf(fout, "Вы будете в шоке, но $ 0 \\cdot ");
    printNode(node->right);
    fprintf(fout, " = 0$ \\\\ \n ");
}

void TexOutput::optMl0(const Node* node)
{
    fprintf(fout, "Интересный факт: $");
    printNode(node->right);
    fprintf(fout, " \\ \\cdot 0 = 0$ \\\\ \n ");
}

void TexOutput::opt0del(const Node* node)
{
    fprintf(fout, "Заметим, что $ \\frac{0}{");
    printNode(node->right);
    fprintf(fout, "} = 0$ \\\\ \n ");
}

void TexOutput::optSb0(const Node* node)
{
    fprintf(fout, "А вы знали, что: $ ");
    printNode(node->right);
    fprintf(fout, " - 0 = ");
    printNode(node->right);
    fprintf(fout, "$ \\\\ \n ");
}

void TexOutput::opt0sb(const Node* node)
{
    fprintf(fout, "Совсем не тривиально: $ 0 - ");
    printNode(node->right);
    fprintf(fout, "  = -");
    printNode(node->right);
    fprintf(fout, "$ \\\\ \n ");
}


