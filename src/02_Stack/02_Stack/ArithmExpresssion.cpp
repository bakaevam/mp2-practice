/*#include "Stack.h"
#include <cmath>
#include <cstring>
#include <iostream>
using namespace std;

char* PostfixForm(char* );
bool SignComparison(char , Stack<char>& );

bool SignComparison(char tmp, Stack<char>& _sign)
{
    // true - ���������� �� � ������ ����
    //false - �� ����������
    if ((_sign.elem[_sign.top - 1] == '*') && (tmp == '*'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '*') && (tmp == '/'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '*') && (tmp == '+'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '*') && (tmp == '-'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '*') && (tmp == '('))
        return true;

    if ((_sign.elem[_sign.top - 1] == '/') && (tmp == '/'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '/') && (tmp == '*'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '/') && (tmp == '+'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '/') && (tmp == '-'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '/') && (tmp == '('))
        return true;

    if ((_sign.elem[_sign.top - 1] == '+') && (tmp == '*'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '+') && (tmp == '/'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '+') && (tmp == '+'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '+') && (tmp == '-'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '+') && (tmp == '('))
        return true;

    if ((_sign.elem[_sign.top - 1] == '-') && (tmp == '*'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '-') && (tmp == '/'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '-') && (tmp == '+'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '-') && (tmp == '-'))
        return true;
    if ((_sign.elem[_sign.top - 1] == '-') && (tmp == '('))
        return true;

    if ((_sign.elem[_sign.top - 1] == '(') && (tmp == '*'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '(') && (tmp == '/'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '(') && (tmp == '+'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '(') && (tmp == '-'))
        return false;
    if ((_sign.elem[_sign.top - 1] == '(') && (tmp == '('))
        return true;

    return false;
};

char* PostfixForm(char* exp)
{
    Stack<char> Sign(10), Operands(10);
    const char* _exp = exp;
    char _size = sizeof(exp);

    for (int i = 0; i < _size; i++)
    {
        //���� ������ ����
        if ((_exp[i] == '*') || (_exp[i] == '/') ||
            (_exp[i] == '+') || (_exp[i] == '-') || (_exp[i] == '('))
        {
            if (SignComparison(_exp[i], Sign)) // ������� ��������� ����� �� ������ � ����������� �����
                Sign.Push(_exp[i]);
        }

        //���� ������ �����
        if (isalpha(_exp[i]))
            Operands.Push(_exp[i]);

        //���� ������ ')'
        if (_exp[i] == ')')
        {
            int j = 0;
            do{
                if (Sign.GetTop() != '(')
                    Operands.Push(Sign.Pop());
                if (Sign.elem[Sign.GetTop() - 1] == '(')
                {
                    Sign.Pop();
                    break;
                }
            } while (Sign.elem[Sign.GetTop() - 1] != '(');
        }
    };
    //����� �� �����
    while (!Sign.IsEmpty())
        Operands.Push(Sign.Pop());
    cout << "/n" << Operands << endl;
    return Operands.elem;
};*/