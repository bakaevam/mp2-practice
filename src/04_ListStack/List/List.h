#ifndef _LIST_H_
#define _LIST_H_
#include "Node.h"
#include <iostream>

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
};

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

    if (_list->pFirst == nullptr)
        pFirst = nullptr;
    else
    {
        pFirst = new TNode<TKey, TData>(*_list.pFirst);
        pFirst->pNext = nullptr;
        pCurr = pFirst;

        _list.Reset();

        TNode* pTmp = _list->pFirst;
        while (!pTmp)
        {
            this->InsertToEnd(_list->pCurr->Key);
            pTmp = pTmp->pNext;
        };
    };
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
}

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::Search(TKey _key)
{
    while (!IsEnded())
    {
        if (pCurr->Key == Key)
        {
            Reset();
            return pCurr;
        };
        Next();
    }

    Reset();
    return nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToStart(TKey Key, TData* _data)
{
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
void TList<TKey, TData>::InsertAfter(TKey Key, TKey newKey, TData* _data)
{
    Reset();

    TNode<TKey, TData>* node = Search(Key);
    if (node == nullptr)
        throw "  Key didn't find";

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(Key, _data);
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

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(Key, _data, pCurr);
    pNext = pCurr;
    pPrev->pNext = _node;
    pCurr = _node;

    Reset();
    return;
};

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey Key)
{
    Reset();

    if (!pFirst)
        throw "  List is Empty";

    if (pFirst->Key == Key)
    {
        delete pFirst;
        pFirst = pNext;
        return;
    }

    TNode<TKey, TData>* node = Search(Key);

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
    //pNext = pFirst->pNext;
};

template<class TKey, class TData>
bool TList<TKey, TData>::IsEnded() const
{
    if ((pCurr == nullptr) || (pNext == nullptr))
        return true;
    return false;
};

template<class TKey, class TData>
void TList<TKey, TData>::Next()
{
    pPrev = pCurr;
    pCurr = pNext;
    pNext = pCurr->pNext;
};
#endif 