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
#endif
