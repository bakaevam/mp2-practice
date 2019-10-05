#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
#include <exception>
#include <cstdio>
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
    int GetTop() const;

    friend ostream& operator<<(ostream& os, const Stack& tmp)
    {
        for (int i = 0; i < tmp.top; i++)
            os << tmp.elem[i];
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
    for (int i = 0; i < size; i++)
        elem[i] = tmp.elem[i];
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
int Stack<ValType>::GetTop() const
{
    return top;
};


int Priority(char sign)
{
    switch (sign)
    {
    case '*' : return 1;
    case '/' : return 1;
    case '+' : return 2;
    case '-' : return 2;
    default: return 4;
    }
}

bool SignComparison(char tmp, Stack<char>& _sign)
{
    // true - ���������� �� � ������ ����
    //false - �� ����������
    if (Priority(_sign.elem[_sign.top - 1]) < Priority(tmp))
        return true;
    else return false;
};

char* PostfixForm(char* exp, int &S)
{
    Stack<char> Sign(25), Operands(25);
    const char* _exp = exp;
    char _size = strlen(exp);

    for (int i = 0; i < _size; i++)
    {
        //���� ������ ����
        if ((_exp[i] == '*') || (_exp[i] == '/') ||
            (_exp[i] == '+') || (_exp[i] == '-'))
        {
            if (SignComparison(_exp[i], Sign)) // ������� ��������� ����� �� ������� 
                //� ����������� �����
            {
                while (Sign.top != 0)
                    Operands.Push(Sign.Pop());
                Sign.Push(_exp[i]);
            }
            else
            {
                Sign.Push(_exp[i]);
            };
        }

        if (_exp[i] == '(')
            Sign.Push(_exp[i]);

        //���� ������ �����
        if (isalpha(_exp[i]))
            Operands.Push(_exp[i]);

        //���� ������ ')'
        if (_exp[i] == ')')
            while (Sign.top != 0)
            {
                if (Sign.elem[Sign.top - 1] != '(')
                    Operands.Push(Sign.Pop());
                else
                {
                    Sign.Pop();
                    break;
                }
            }
    };
    //����� �� �����
    while (!Sign.IsEmpty())
        Operands.Push(Sign.Pop());
    cout << "\n  Postfix Form: " << Operands << endl;

    S = Operands.top; // ����� ����������� �����
    return Operands.elem;
};

float CountingValue(char* PostForm, int S)
{
    cout << PostForm;
    Stack<float> numbers(25);
    Stack<char> letters(25);
    const char* _PostForm = PostForm;
    char _size = S;
    float a = 0, b = 0;
    float count = 0;

    for (int i = 0; i < _size; i++)
    {
        if (isalpha(PostForm[i]))
        {
            letters[i] = _PostForm[i];
            cout << "\n  " << letters[i] << " = ";
            cin >> numbers[i];
        }
        if ((_PostForm[i] == '*') || (_PostForm[i] == '/') ||
            (_PostForm[i] == '+') || (_PostForm[i] == '-'))
        {
            a = numbers.Pop();
            b = numbers.Pop();
            if (_PostForm[i] == '*') count = b * a;
            if (_PostForm[i] == '/') count = b / a;
            if (_PostForm[i] == '+') count = b + a;
            if (_PostForm[i] == '-') count = b - a;
            numbers.Push(count);
        }
    }
    return numbers.elem[numbers.top - 1];
}

#endif
