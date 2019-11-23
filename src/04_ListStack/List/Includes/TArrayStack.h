#ifndef  _TARRAYSTACK_H_
#define _TARRAYSTACK_H_
#include <iostream>
#include "TStack.h"
#include "Exception.h"
using namespace std;

template<class ValType>
class TArrayStack : public TStack<ValType>
{
private:
    int size;
    int top;
    ValType* elem;
public:
    TArrayStack(int max);
    TArrayStack(const TArrayStack&);
    ~TArrayStack();

    void Push(ValType);
    ValType TopPop() const;
    void Pop();
    bool IsEmpty() const;
    bool IsFull() const;

    friend ostream& operator<<(ostream& os, const TArrayStack& tmp)
    {
        cout << "\n  ";
        while (!tmp.IsEmpty())
            for (int i = 0; i < tmp.top; i++)
                os << " " << tmp.elem[i];
        return os;
    };
};

/////  IMPLEMENTATION TARRAY STACK/////
template<class ValType>
TArrayStack<ValType>::TArrayStack(int max): size(max)
{
    top = 0;
    elem = new ValType[size];
    for (int i = 0; i < size; i++)
        elem[i] = 0;
};

template<class ValType>
TArrayStack<ValType>::TArrayStack(const TArrayStack& tmp): size(tmp.size), top(tmp.top)
{
    elem = new ValType[size];
    for (int i = 0; i < size; i++)
        elem[i] = tmp.elem[i];
};

template<class ValType>
TArrayStack<ValType>::~TArrayStack()
{
    size = 0;
    top = 0;
    delete[] elem;
};

template<class ValType>
void TArrayStack<ValType>::Push(ValType num)
{
    if (IsFull())
        throw Exception_errors("  Stack is full");
    elem[top++] = num;
};

template<class ValType>
ValType TArrayStack<ValType>::TopPop() const
{
    if (IsEmpty())
        throw Exception_errors("  Stack is empty");
    return elem[top - 1];
};

template<class ValType>
void TArrayStack<ValType>::Pop()
{
    if (IsEmpty())
        throw Exception_errors("  Stack is empty");
    top--;
};

template<class ValType>
bool TArrayStack<ValType>::IsEmpty() const
{
    if (top == 0)
        return true;
    return false;
};

template<class ValType>
bool TArrayStack<ValType>::IsFull() const
{
    if ((top + 1) == size)
        return true;
    return false;
};

#endif