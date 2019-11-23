#ifndef  _TLIST_H_
#define _TLIST_H_
#include <iostream>
#include "TNode.h"
#include "Exception.h"
using namespace std;

template<typename TKey, class TData>
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
    TNode<TKey, TData>* GetpFirst() const;

    void Reset();
    bool IsEnded() const;
    void Next();

    template<class TKey, class TData>
    friend ostream& operator<<(ostream& os, TList<TKey, TData>& tmp);

    template<class ValType>
    friend class TListStack;
};

template<typename TKey, typename TData>
TList<TKey, TData>::TList()
{
    pFirst = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;
};

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& _list)
{
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;

    if (!_list.pFirst)
        pFirst = nullptr;
    else
    {
        pFirst = new TNode<TKey, TData>(*_list.pFirst);
        pFirst->pNext = nullptr;
        pCurr = pFirst;

        TNode<TKey, TData>* i = new TNode<TKey, TData>;
        i = _list.pFirst;

        while (i->pNext)
        {
            i = i->pNext;
            pCurr->pNext = new TNode<TKey, TData>(*i);
            pPrev = pCurr;
            pCurr = pCurr->pNext;
            pNext = pCurr->pNext = nullptr;
        }

        pPrev = nullptr;
        pCurr = pFirst;
        pNext = pFirst->pNext;
    }
};

template<class TKey, class TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _first)
{
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;

    if (!_first)
        pFirst = nullptr;
    else
    {
        TNode<TKey, TData>* node = new TNode<TKey, TData>(*_first);
        pFirst = node;
        TNode<TKey, TData>* prev = pFirst;
        TNode<TKey, TNode>* i = _first->pNext;

        while (i)
        {
            TNode<TKey, TNode>* tmp = new TNode<TKey, TData>(*i);
            prev->pNext = tmp;
            prev = tmp;
            i = i->pNext;
        }

        pCurr = pFirst;
        pNext = pCurr->pNext;
    }
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
    TNode<TKey, TData>* prev = pPrev;
    TNode<TKey, TData>* next = pNext;
    TNode<TKey, TData>* curr = pCurr;

    Reset();
    while (!IsEnded())
    {
        if (pCurr->Key == _key)
        {
            TNode<TKey, TData>* find = pCurr;
            pCurr = curr;
            pPrev = prev;
            pNext = next;
            return find;
        }
        Next();
    };

    pPrev = prev;
    pNext = next;
    pCurr = curr;

    return nullptr;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToStart(TKey _Key, TData* _data)
{
    if (pFirst == nullptr)
    {
        pFirst = new TNode<TKey, TData>(_Key, _data);
        pCurr = pFirst;
        return;
    };

    TNode<TKey, TData>* node = new TNode<TKey, TData>(_Key, _data, pFirst);
    node->pNext = pFirst;
    if (pCurr == pFirst)
        pPrev = node;
    pFirst = node;

};

template<class TKey, class TData>
void TList<TKey, TData>::InsertToEnd(TKey _Key, TData* _data)
{
    TNode<TKey, TData>* prev = pPrev;
    TNode<TKey, TData>* next = pNext;
    TNode<TKey, TData>* curr = pCurr;

    TNode<TKey, TData>* node = new TNode<TKey, TData>(_Key, _data);

    if (!pFirst)
        pFirst = node;
    else
        pCurr->pNext = node;

    if (curr == pCurr)
        pNext = node;
    else
        pNext = next;

    pCurr = curr;
    pPrev = prev;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertAfter(TKey _Key, TKey newKey, TData* _data)
{
    TNode<TKey, TData>* prev = pPrev;
    TNode<TKey, TData>* next = pNext;
    TNode<TKey, TData>* curr = pCurr;

    Reset();

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
        throw Exception_errors("  Key didn't find");

    while (pCurr != node)
        Next();

    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data);
    pCurr->pNext = _node;

    if (curr == pCurr)
        pNext = node;
    else
        pNext = next;

    if (curr == pNext)
        pPrev = node;
    else
        pPrev = prev;

    pCurr = curr;
};

template<class TKey, class TData>
void TList<TKey, TData>::InsertBefore(TKey _Key, TKey newKey, TData* _data)
{
    TNode<TKey, TData>* prev = pPrev;
    TNode<TKey, TData>* next = pNext;
    TNode<TKey, TData>* curr = pCurr;

    Reset();

    if ((IsEnded()) || (pFirst->Key == _Key))
    {
        InsertToStart(newKey, _data);
        pCurr = pFirst;
        return;
    }

    TNode<TKey, TData>* node = Search(_Key);
    if (node == nullptr)
    {
        throw Exception_errors("  Key didn't find");
        return;
    }

    while (pCurr != node)
        Next();
    TNode<TKey, TData>* _node = new TNode<TKey, TData>(newKey, _data, pCurr);
    pPrev->pNext = _node;

    if (curr == pPrev)
        pNext = node;
    else
        pNext = next;

    if (curr == pCurr)
        pPrev = node;
    else
        pPrev = prev;

    pCurr = curr;
};

template<class TKey, class TData>
void TList<TKey, TData>::Remove(TKey _Key)
{
    if (!pFirst)
        throw Exception_errors("  List is Empty");

    if (pFirst->Key == _Key)
    {
        if (pCurr == pFirst)
        {
            pCurr = pNext;
            if (pNext)
                pNext = pNext->pNext;
            else
                pNext = nullptr;

            delete pFirst;
            pFirst = pCurr;

            return;
        }

        if (pCurr == pFirst->pNext)
        {
            pPrev = nullptr;

            delete pFirst;
            pFirst = pCurr;
            return;
        }
        delete pFirst;

        return;
    }

    TNode<TKey, TData>* curr = pCurr;
    TNode<TKey, TData>* prev = pPrev;
    TNode<TKey, TData>* next = pNext;

    Reset();
    TNode<TKey, TData>* node = Search(_Key);

    if (node == nullptr)
        throw Exception_errors("Error: key didn't find!");

    while (pCurr != node)
        Next();

    pPrev->pNext = pNext;

    if (curr == pCurr)
    {
        pCurr = next;
        pNext = pCurr->pNext;
        delete node;

        return;
    }

    if (curr == pNext)
    {
        pCurr = pNext;
        pNext = pCurr->pNext;
        delete node;

        return;
    }

    if (curr == pPrev)
    {
        pCurr = pPrev;
        pPrev = prev;
        pNext = pCurr->pNext;
        delete node;

        return;
    }

    pNext = curr->pNext;
    pCurr = curr;
    delete node;

    return;
};

template<class TKey, class TData>
TNode<TKey, TData>* TList<TKey, TData>::GetpFirst() const
{
    return pFirst;
};

template<class TKey, class TData>
void TList<TKey, TData>::Reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
    if (pFirst)
        pNext = pCurr->pNext;
    else
        pNext = nullptr;
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
    pPrev = pCurr;
    pCurr = pNext;

    if (pCurr)
        pNext = pCurr->pNext;
    else
        pNext = nullptr;;
};

template<class TKey, class TData>
ostream& operator<<(ostream& os, TList<TKey, TData>& tmp)
{
    TNode<TKey, TData>* curr = tmp.pCurr;
    TNode<TKey, TData>* prev = tmp.pPrev;
    TNode<TKey, TData>* next = tmp.pNext;

    tmp.Reset();

    while (!tmp.IsEnded())
    {
        os << "  " << tmp.pCurr->Key << " ";
        tmp.Next();
    }

    os << endl;

    tmp.pCurr = curr;
    tmp.pPrev = prev;
    tmp.pNext = next;

    return os;
}

#endif