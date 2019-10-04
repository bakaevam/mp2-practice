#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
#include <exception>
using namespace std;

template<class ValType>
class Stack
{
public:
    int size;
    int top;
    ValType* elem;
public:
    Stack(int max);
    Stack(const Stack&);
    ~Stack();

    void Push(ValType);
    ValType Pop();
    bool IsEmpty() const;
    bool IsFull() const;
    ValType& operator[](int);
    const ValType& operator[](int) const;
    int GetTop() const;

    friend ostream& operator<<(ostream& os, const Stack& tmp)
    {
        for (int i = 0; i < tmp.size; i++)
            os << tmp.elem[i] << " ";
        return os;
    };
};

template<class ValType>
Stack<ValType>::Stack(int max)
{
    size = max;
    top = 0;
    elem = new ValType[size];
};

template<class ValType>
Stack<ValType>::Stack(const Stack& tmp)
{
    size = tmp.size;
    top = tmp.top;
    elem = new ValType[size];
    memcpy(elem, tmp.elem, sizeof(Valtype) * size);
};

template<class ValType>
Stack<ValType>::~Stack()
{
    size = 0;
    top = 0;
    delete[] elem;
};

template<class ValType>
void Stack<ValType>::Push(ValType num)
{
    if (IsFull())
        throw "  Stack is full";
    elem[top++] = num;
};

template<class ValType>
ValType Stack<ValType>::Pop()
{
    if (IsEmpty())
        throw "  Stack is empty";
    return elem[--top];
};

template<class ValType>
bool Stack<ValType>::IsEmpty() const
{
    if (top == 0)
        return true;
    return false;
};

template<class ValType>
bool Stack<ValType>::IsFull() const
{
    if (top == size)
        return true;
    return false;
};

template<class ValType>
ValType& Stack<ValType>::operator[](int ind)
{
    if ((ind < 0) || (ind >= size))
        throw "Index is not correct!";

    return elem[ind];
};

template<class ValType>
const ValType& Stack<ValType>::operator[](int ind) const
{
    if ((ind < 0) || (ind >= size))
        throw "Index is not correct!";

    return elem[ind];
};

template<class ValType>
int Stack<ValType>::GetTop() const
{
    return top;
};


char* PostfixForm(char*);
bool SignComparison(char, Stack<char>&);

bool SignComparison(char tmp, Stack<char>& _sign)
{
    // true - перемещаем всё в другой стек
    //false - не перемещаем
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
        //Если пришел знак
        if ((_exp[i] == '*') || (_exp[i] == '/') ||
            (_exp[i] == '+') || (_exp[i] == '-') || (_exp[i] == '('))
        {
            if (SignComparison(_exp[i], Sign)) // функция сравнения знака на вершне и приходящего знака
                Sign.Push(_exp[i]);
        }

        //Если пришла буква
        if (isalpha(_exp[i]))
            Operands.Push(_exp[i]);

        //Если пришла ')'
        if (_exp[i] == ')')
        {
            int j = 0;
            do {
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
    //Дошли до конца
    while (!Sign.IsEmpty())
        Operands.Push(Sign.Pop());
    cout << "/n" << Operands << endl;
    return Operands.elem;
};
#endif
