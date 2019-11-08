#ifndef _TLIST_H_
#define _TLIST_H_
#include "TNode.h"
#include <iostream>
using namespace std;

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

    template<class TKey, class TData>
    friend class TListStack;
};

template<class TKey, class TData>
class TListStack : public TStack<ValType>
{
private:
    TList<TKey, TData>* List;
public:
    TListStack();
    TListStack(const TListStack&);
    ~TListStack();

    void Push(TKey, TData*);
    TNode<TKey, TData> TopPop() const;
    void Pop();
    bool IsEmpty() const;
    bool IsFull() const;
};
//////////////////////////////////////////////////
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
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;

    if (_list.pFirst == nullptr)
    {
        pFirst = nullptr;
    }
    else
    {
        pFirst = new TNode<TKey, TData>(*_list.pFirst);
        pFirst->pNext = nullptr;
        pCurr = pFirst;

        _list.Reset();

        while (!_list.IsEnded())
        {
            _list.Next();
            pCurr->pNext = new TNode<TKey, TData>(*_list.pCurrent);

            pPrev = pCurr;
            pCurr = pCurr->pNext;
            pNext = pCurr->pNext;
            pNext = nullptr;
        }
    }
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

    while (!IsEnded())
    {
        if (pCurr->Key == Key)
            return pCurr;
        Next();
    }

    Reset();
    return nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToStart(TKey Key, TData* _data)
{
    if (pCurr != nullptr)
        Reset();
    TNode<TKey, TData>* node = new TNode<TKey, TData>(Key, _data, pFirst);
    pNext = pFirst;
    pFirst = node;
    pCurr = pFirst;
    Reset();
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToEnd(TKey Key, TData* _data)
{
    Reset();
    while (!IsEnded())
        Next();

    TNode<TKey, TData>* node = new TNode<TKey, TData>(Key, _data);
    pCurr->pNext = node;
    Reset();
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey _Key, TKey newKey, TData* _data)
{
    Reset();

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
        throw "  Key didn't find";

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data);
    pCurr->pNext = _node;
    pPrev = pCurr;
    pCurr = node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey Key, TKey newKey, TData* _data)
{
    Reset();

    if (IsEnded())
    {
        InsertToStart(newKey, _data);
        return;
    }

    TNode<TKey, TData>* node = Search(Key);
    if (node == nullptr)
        throw "  Key didn't find";

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data, pCurr);
    pNext = pCurr;
    pPrev->pNext = _node;
    pCurr = _node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey _Key)
{
    Reset();

    if (!pFirst)
        throw "  List is Empty";

    if (pFirst->Key == Key)
    {
        delete pFirst;
        pFirst = pNext;
        Reset();
        return;
    }

    TNode<TKey, TData>* node = Search(_Key);

    if (node == nullptr)
        throw "  Key didn't find";

    pPrev->pNext = pNext;
    delete node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
    pNext = pCurr->pNext;
};

template<class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
    if (pFirst == nullptr)
        return true;
    return false;
};

template<class TKey, class TData>
void TList<TKey, TData>::Next()
{
    pPrev = pCurr;
    pCurr = pNext;

    if(pCurr)
        pNext = pCurr->pNext;
    else pNext = nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::Print()
{
    Reset();

    while (!IsEnded())
    {
        cout << pCurr->Key;
        Next();
    }
};

//////////////////////////////////////////////////////////////////

template<class TKey, class TData>
TListStack<TKey, TData>::TListStack()
{
    List = new TList<TKey, TData>;
};

template<class TKey, class TData>
TListStack<TKey, TData>::TListStack(const TListStack& tmp)
{
    List = tmp;
};

template<class TKey, class TData>
TListStack<TKey, TData>::~TListStack()
{
    delete List;
};

template<class TKey, class TData>
void TListStack<TKey, TData>::Push(TKey _key, TData* _data)
{
    List->InsertToStart(_key, _data);
};

template<class TKey, class TData>
TNode<TKey, TData> TListStack<TKey, TData>::TopPop() const
{
    return List->pFirst;
};

template<class TKey, class TData>
void TListStack<TKey, TData>::Pop()
{
    List->Remove(List->pFirst->Key);
};

template<class TKey, class TData>
bool TListStack<TKey, TData>::IsEmpty() const
{
    if (List->pFirst == nullptr)
        return true;
    else return false;
};

template<class TKey, class TData>
bool TListStack<TKey, TData>::IsFull() const
{
    TNode<TKey, TData>* tmp
}
#endif 