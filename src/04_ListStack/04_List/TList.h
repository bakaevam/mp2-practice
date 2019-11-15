#ifndef _TLIST_H_
#define _TLIST_H_
#include "TNode.h"
#include "Exception.h"
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

	template<class TKey, class TData>
	friend ostream& operator<<(ostream& os, const TList<TKey, TData>& tmp)
	{
		TNode<TKey, TData>* node = tmp.pFirst;
		while (node != 0)
		{
			cout << "  " << node->Key << " ";
			node = node->pNext;
		}
		cout << endl;
		return os;
	}
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
	TNode<TKey, TNode>* prev = pPrev;
	TNode<TKey, TNode>* next = pNext;
	TNode<TKey, TNode>* curr = pCurr;

    Reset();
    while (pCurr != nullptr)
    {
        if (pCurr->Key == _key)
            return pCurr;
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
        TNode<TKey, TData>* node = new TNode<TKey, TData>(newKey, _data);
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

#endif 