#ifndef  _TSTACK_H_
#define _TSTACK_H_
#include <iostream>
#include "TNode.h"
#include "Exception.h"
using namespace std;

enum StackType
{
    Array,
    List,
};

template<class ValType>
class TStack
{
public:
    static TStack* Create(StackType);

    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual void Push(ValType) = 0;
    virtual void Pop() = 0;
    virtual ValType TopPop() const = 0;
};

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

//// CLASS TLIST ////

template<class TKey, class TData>
class TList
{
private:
    TNode<TKey, TData>* pFirst;
    TNode<TKey, TData>* pCurr;
    TNode<TKey, TData>* pNext;
    TNode<TKey, TData>* pPrev;

public:
    TList();
    TList(const TList&);
    TList(const TNode<TKey, TData>*);
    ~TList();

    TNode<TKey, TData>* Search(TKey);
    void InsertToStart(TKey, TData*);
    void InsertToEnd(TKey, TData*);
    void InsertAfter(TKey, TKey, TData*);
    void InsertBefore(TKey, TKey, TData*);
    void Remove(TKey);

    void Reset();
	bool IsEnded() const;
    void Next();

    void Print();
    TNode<TKey, TData>* GetpFirst() const;

    template<class ValType>
    friend class TListStack;
};

//// CLASS TLISTSTACK ////

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

/////  IMPLEMENTATION TSTACK/////

template<class ValType>
TStack<ValType>* TStack<ValType>::Create(StackType type)
{
    if (type == Array)
        return new TArrayStack<ValType>(100);
    if(type == List)
        return new TListStack<ValType>();
    throw Exception_errors(" Stack Type isn't correct");
};

/////  IMPLEMENTATION TARRAY STACK/////
template<class ValType>
TArrayStack<ValType>::TArrayStack(int max)
{
    size = max;
    top = 0;
    elem = new ValType[size];
    for (int i = 0; i < size; i++)
        elem[i] = 0;
};

template<class ValType>
TArrayStack<ValType>::TArrayStack(const TArrayStack& tmp)
{
    size = tmp.size;
    top = tmp.top;
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

///// IMPLEMENTATION TLIST /////
template<class TKey, class TData>
TList<TKey, TData>::TList()
{
    pFirst = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
TList<TKey, TData>::TList(const TList& _list)
{
    pFirst = new TNode<TKey, TData>(*_list.pFirst);
    TNode<TKey, TData>* node = pFirst;
    TNode<TKey, TData>* tmp = _list.pFirst;
    while (tmp->pNext != nullptr)
    {
        node->pNext = new TNode<TKey, TData>(*tmp->pNext);
        node = node->pNext;
        tmp = tmp->pNext;
    }
    pPrev = nullptr;
    pNext = nullptr;
    pCurr = pFirst;
};

template<class TKey, class TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _first)
{
    pFirst = _first;
    pCurr = pFirst;
    pPrev = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
TList<TKey, TData>::~TList()
{
    Reset();
    while (!IsEnded())
    {
        Next();
        delete pPrev;
    }

    delete pCurr;
    pFirst = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
    Reset();
    while (pCurr != nullptr)
    {
        if (pCurr->Key == _key)
            return pCurr;
        Next();
    };

    Reset();
    return nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToStart(TKey _Key, TData* _data)
{
    if (pCurr != nullptr)
        Reset();
    TNode<TKey, TData>* node = new TNode<TKey, TData>(_Key, _data);
    node->pNext = pFirst;
    pNext = pFirst;
    pFirst = node;
    pCurr = pFirst;
    Reset();
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToEnd(TKey _Key, TData* _data)
{
    Reset();
    while (!IsEnded())
        Next();

    TNode<TKey, TData>* node = new TNode<TKey, TData>(_Key, _data);
    pPrev->pNext = node;
    Reset();
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey _Key, TKey newKey, TData* _data)
{
    Reset();

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
        throw Exception_errors("  Key didn't find");

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data);
    _node->pNext = node->pNext;
    node->pNext = _node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey _Key, TKey newKey, TData* _data)
{
    Reset();

    if (IsEnded())
    {
        InsertToStart(newKey, _data);
        return;
    }

    if (pFirst->Key == _Key)
    {
        TNode<TKey,TData>* node = new TNode<TKey, TData>(newKey, _data);
        node->pNext = pFirst;
        pFirst = node;
        return;
    }

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
        throw Exception_errors("  Key didn't find");

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data);
    _node->pNext = pCurr;
    pPrev->pNext = _node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey _Key)
{
    Reset();

    if (!pFirst)
        throw Exception_errors("  List is Empty");

    if (pFirst->Key == _Key)
    {
        delete pFirst;
        pFirst = pNext;
        Reset();
        return;
    }

    TNode<TKey, TData>* node = Search(_Key);

    if (node == nullptr)
        throw Exception_errors("  Key didn't find");

    pPrev->pNext = pNext;
    delete node;

    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Reset()
{
    pNext = pCurr->pNext;
    pCurr = pFirst;
    pPrev = nullptr;
};

template<class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
    if (pCurr == nullptr)
        return true;
    return false;
};

template<class TKey, class TData>
void TList<TKey, TData>::Next()
{
    if (pCurr->pNext == nullptr)
    {
        pPrev = pCurr;
        pCurr = pNext;
        pNext = nullptr;
    }
    else
    {
        pPrev = pCurr;
        pCurr = pNext;
        pNext = pNext->pNext;
    };
};

template<class TKey, class TData>
void TList<TKey, TData>::Print()
{
    Reset();
    TNode<TKey, TData>* tmp = pFirst;
    while (tmp != 0)
    {
        cout << "  " << tmp->Key <<" ";
        tmp = tmp->pNext;
    }
    cout << endl;
};

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::GetpFirst() const
{
    return pFirst;
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
    delete[] ListElem;
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
    if (ListElem->GetpFirst() == nullptr)
        return true;
    else return false;
};

template<class ValType>
bool TListStack<ValType>::IsFull() const
{
    TNode<ValType, ValType>* tmp = new TNode<ValType, ValType>();
    return !tmp;
};
#endif

