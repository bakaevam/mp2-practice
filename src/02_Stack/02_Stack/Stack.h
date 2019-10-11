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


/////////////////////////////////////////////
int Priority(char sign)
{
    switch (sign)
    {
    case '*' : return 1;
    case '/' : return 1;
    case '+' : return 2;
    case '-' : return 2;
    default: return 3;
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
            //Проверка на повторяющийся знак
            if ((Operands.elem[Operands.top - 1] == _exp[i]) ||
                (Sign.elem[Sign.top - 1] == _exp[i]))
                continue;
            if (SignComparison(_exp[i], Sign)) // функция сравнения знака на вершине и приходящего знака
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
    char Post[25];
    for (int i = 0; i < S; i++)
        Post[i] = PostForm[i];
    char _size = S;
    char letters[25];
    int numbers[25];
    Stack<int> Value(25);
    int topLetters = 0;

    //Заполнение массива значений
    for(int i = 0; i < S; i++)
        if (isalpha(Post[i]))
        {
            int flag = 0;
            for (int j = 0; j < topLetters; j++)
                if (letters[j] == Post[i])
                {
                    flag = 1;
                    break;
                }
                if(flag == 0)
                {
                    letters[topLetters] = Post[i];
                    cout << "\n  " << letters[topLetters] << " = ";
                    cin >> numbers[topLetters++];
                }
        }

    //Чтение постфиксной записи
    for (int i = 0; i < S; i++)
    {
        if(isalpha(Post[i]))
            for(int j = 0; j < topLetters; j++)
                if (letters[j] == Post[i])
                {
                    Value.Push(numbers[j]);
                }
        if ((Post[i] == '*') || (Post[i] == '/') ||
            (Post[i] == '+') || (Post[i] == '-'))
        {
            int a = Value.Pop();
            int b = Value.Pop();
            if (Post[i] == '*') Value.Push(b * a);
            if (Post[i] == '/') Value.Push(b / a);
            if (Post[i] == '+') Value.Push(b + a);
            if (Post[i] == '-') Value.Push(b - a);
        }
    }
    return Value.Pop();
};

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