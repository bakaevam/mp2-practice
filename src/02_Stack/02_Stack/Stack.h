#ifndef _STACK_H_
#define _STACK_H_
#include "Exception.h"
using namespace std;

template<class ValType>
class Stack
{
private:
    int size;
    int top;
    ValType* elem;
public:
    Stack(int max);
    Stack(const Stack&);
    ~Stack();

    void Push(ValType);
    ValType TopPop() const;
	void Pop();
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
        throw Exception_errors("  Stack is full");
    elem[top++] = num;
};

template<class ValType>
ValType Stack<ValType>::TopPop() const
{
    if (IsEmpty())
        throw Exception_errors("  Stack is empty");
    return elem[top - 1];
};

template<class ValType>
void Stack<ValType>::Pop()
{
	if (IsEmpty())
		throw Exception_errors("  Stack is empty");
	top--;
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
    if ((top + 1) == size)
        return true;
    return false;
};
#endif