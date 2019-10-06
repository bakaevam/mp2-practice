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
    for (int i = 0; i < size; i++)
        elem[i] = 0;
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
    // true - перемещаем всё в другой стек
    //false - не перемещаем
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
        //Если пришел знак
        if ((_exp[i] == '*') || (_exp[i] == '/') ||
            (_exp[i] == '+') || (_exp[i] == '-'))
        {
            if (SignComparison(_exp[i], Sign)) // функция сравнения знака на вершине 
                //и приходящего знака
            {
                while (Sign.top != 0)
                    Operands.Push(Sign.Pop());
                Sign.Push(_exp[i]);
            }
            else
                Sign.Push(_exp[i]);
        }

        if (_exp[i] == '(')
            Sign.Push(_exp[i]);

        //Если пришла буква
        if (isalpha(_exp[i]))
            Operands.Push(_exp[i]);

        //Если пришла ')'
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
    //Дошли до конца
    while (!Sign.IsEmpty())
        Operands.Push(Sign.Pop());
    char tmp[25];
    for (int i = 0; i < Operands.size; i++)
        tmp[i] = Operands.elem[i];
    cout << "\n  Postfix Form: " << tmp << endl;

    S = Operands.top; // Длина постфиксной формы
    return tmp;
};

float CountingValue(char PostForm[], int S)
{
    int Post[25];
    for (int i = 0; i < S; i++)
        Post[i] = PostForm[i];

    Stack<float> numbers(25);
    Stack<char> letters(25);
    char _size = S;
    float a = 0, b = 0;
    float count = 0;

    for (int i = 0; i < _size; i++)
    {
        int flag = 0;
        int j = 0;
        if (isalpha(Post[i]))
        {
            for (j = 0; j < letters.top; j++)
                if (letters[j] == Post[i])
                {
                    flag = 1;
                    break;
                }
            if (flag == 0)
            {
                letters.Push(Post[i]);
                cout << "\n  " << letters[letters.top - 1] << " = ";
                cin >> a;
                numbers.Push(a);
            }
            else numbers.Push(numbers.elem[j]);
        }
        if ((Post[i] == '*') || (Post[i] == '/') ||
            (Post[i] == '+') || (Post[i] == '-'))
        {
            a = numbers.Pop();
            b = numbers.Pop();
            if (Post[i] == '*') count = b * a;
            if (Post[i] == '+') count = b + a;
            if (Post[i] == '-') count = b - a;
            if (Post[i] == '/')
            {
                if (a == 0)
                  //  throw Exception_errors("  You mustn't divide by 0");
                count = b / a;
            }
            numbers.Push(count);
        }
    }
    return numbers.elem[numbers.top - 1];
}

//Exceptions
class Exception_errors : exception
{
private:
    const string mes;
public:
    Exception_errors(string e)
        :mes(e)
    {
    }
    const char* what() const { return mes.c_str(); }
};

#endif
