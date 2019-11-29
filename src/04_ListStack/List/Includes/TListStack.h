#ifndef  _TLISTSTACK_H_
#define _TLISTSTACK_H_
#include <iostream>
#include "TStack.h"
#include "TList.h"
#include "Exception.h"
using namespace std;

template<class ValType>
class TListStack : public TStack<ValType>
{
private:
    TList<ValType, ValType>* ListElem;
public:
    TListStack();
    TListStack(const TListStack&);
    ~TListStack();

    void Push(ValType);
    ValType TopPop() const;
    void Pop();
    bool IsEmpty() const;
    bool IsFull() const;
    
};

///// IMPLEMENTATION TLIST STACK/////

template<class ValType>
TListStack<ValType>::TListStack()
{
    ListElem = new TList<ValType, ValType>;
};

template<class ValType>
TListStack<ValType>::TListStack(const TListStack<ValType>& tmp)
{
    ListElem = new TList<ValType, ValType>(tmp.ListElem);
};

template<class ValType>
TListStack<ValType>::~TListStack()
{
    delete ListElem;
};

template<class ValType>
void TListStack<ValType>::Push(ValType _key)
{
    if (IsFull())
        throw Exception_errors("  Stack is full");
    ListElem->InsertToStart(_key, nullptr);
    ListElem->Reset();
};

template<class ValType>
ValType TListStack<ValType>::TopPop() const
{
    if (IsEmpty())
        throw Exception_errors("  Stack is empty");

    return ListElem->GetpFirst()->Key;
};

template<class ValType>
void TListStack<ValType>::Pop()
{
    if (IsEmpty())
        throw Exception_errors("  Stack is empty");

    ListElem->Remove(ListElem->GetpFirst()->Key);
};

template<class ValType>
bool TListStack<ValType>::IsEmpty() const
{
    return (ListElem->GetpFirst() == nullptr);
};

template<class ValType>
bool TListStack<ValType>::IsFull() const
{
	try
	{
		TNode<ValType, ValType>* tmp = new TNode<ValType, ValType>();
		if (tmp == nullptr)
		{
			return true;
		}
		delete tmp;
		return false;
	}
	catch (...)
	{
		return true;
	}
};

#endif