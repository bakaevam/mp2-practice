#ifndef  _TLIST_POLINOM_H_
#define _TLIST_POLINOM_H_
#include <iostream>
#include "TNode_Polinom.h"
#include "TList.h"
#include "Exception.h"
using namespace std;

template<>
class TList<int, float>
{
private:
    TNode<int, float>* pCurr;
    TNode<int, float>* pNext;
    TNode<int, float>* pPrev;
    TNode<int, float>* pFirst;
public:
    TList();
    TList(const TList&);
    TList(const TNode<int, float>*);
    ~TList();

    void Simple();
    void Sort();
    void swap(TNode<int, float>*, TNode<int, float>*);
    int Count();
    TNode<int, float>*Search(int);
    void InsertToStart(int, float);
    void InsertToEnd(int, float);
    void InsertAfter(int, int, float);
    void InsertBefore(int, int, float);
    void Remove(int);
    TNode<int, float>* GetpFirst() const;
    TNode<int, float>* GetpCurr() const;
    TNode<int, float>* GetpPrev() const;

    void Reset();
    bool IsEnded() const;
    void Next();

    friend ostream& operator<<(ostream& os, TList<int, float>& tmp)
    {
        TNode<int, float>* curr = tmp.pCurr;
        TNode<int, float>* prev = tmp.pPrev;
        TNode<int, float>* next = tmp.pNext;

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
    };
    

    template<class ValType>
    friend class TListStack;
};

TList<int, float>::TList()
{
    pFirst = nullptr;
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;
};

TList<int, float>::TList(const TList& _list)
{
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;

    if (!_list.pFirst)
        pFirst = nullptr;
    else
    {
        pFirst = new TNode<int, float>(*_list.pFirst);
        pFirst->pNext = nullptr;
        pCurr = pFirst;

        TNode<int, float>* i = new TNode<int, float>;
        i = _list.pFirst;

        while (i->pNext)
        {
            i = i->pNext;
            pCurr->pNext = new TNode<int, float>(*i);
            pPrev = pCurr;
            pCurr = pCurr->pNext;
            pNext = pCurr->pNext = nullptr;
        }

        pPrev = nullptr;
        pCurr = pFirst;
        pNext = pFirst->pNext;
    }
};

TList<int, float>::TList(const TNode<int, float>* _first)
{
    pCurr = nullptr;
    pPrev = nullptr;
    pNext = nullptr;

    if (!_first)
        pFirst = nullptr;
    else
    {
        TNode<int, float>* node = new TNode<int, float>(*_first);
        pFirst = node;
        TNode<int, float>* prev = pFirst;
        TNode<int, float>* i = _first->pNext;

        while (i)
        {
            TNode<int, float>* tmp = new TNode<int, float>(*i);
            prev->pNext = tmp;
            prev = tmp;
            i = i->pNext;
        }

        pCurr = pFirst;
        pNext = pCurr->pNext;
    }
};

TList<int, float>::~TList()
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
};

void TList<int, float>::Simple()
{
    Reset();

    while (!IsEnded())
    {
        TNode<int, float>* tmp = pFirst;

            while ((tmp->Key != pCurr->Key))
            {
                tmp = tmp->pNext;
            };

            if (tmp == pCurr)
            {
                Next();
                continue;
            };

            pCurr->data += tmp->data;
            Remove(tmp->Key);
            Next();
    };
};

void TList<int, float>::Sort()
{
    if (pFirst == nullptr)
        return;

    if (pFirst->pNext == nullptr)
        return;

    Reset();

    TNode<int, float>* t, *m, *a, *b;
    for (bool isDone = true; isDone;)
    {
        isDone = false;
        a = t = pFirst;
        b = pFirst->pNext;

        while (b != nullptr)
        {
            if (a->Key < b->Key)
            {
                if (t == a)
                    pFirst = b;
                else t->pNext = b;

                a->pNext = b->pNext;
                b->pNext = a;

                m = a;
                a = b;
                b = m;
                isDone = true;
            }
            t = a;
            a = a->pNext;
            b = b->pNext;
        }
   }
};

void TList<int, float>::swap(TNode<int, float>* a, TNode<int, float>* b)
{
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;
    TNode<int, float>* curr = pCurr;
    Reset();

    TNode<int, float> *aPrev, *aNext, *bPrev, *bNext;

    while (pCurr != a)
        Next();
    aPrev = pPrev;
    aNext = b;
    Reset();

    bPrev = a;
    bNext = b->pNext;

    if (a != pFirst)
    {
        aPrev->pNext = b;
        b->pNext = a;
        a->pNext = bNext;
    }
    else
    {
        a->pNext = bNext;
        b->pNext = a;
        pFirst = b;
    }

    pPrev = prev;
    pNext = next;
};

int TList<int, float>::Count()
{
    TNode<int, float>* tmp = pFirst;
    int count = 0;
    while (tmp != nullptr)
    {
        count++;
        tmp = tmp->pNext;
    }
    return count;
};

TNode<int, float>* TList<int, float>::Search(int _key)
{
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;
    TNode<int, float>* curr = pCurr;

    Reset();
    while (!IsEnded())
    {
        if (pCurr->Key == _key)
        {
            TNode<int, float>* find = pCurr;
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

void TList<int, float>::InsertToStart(int _Key, float _data)
{
    if (pFirst == nullptr)
    {
        pFirst = new TNode<int, float>(_Key, _data);
        pCurr = pFirst;
        return;
    };

    TNode<int, float>* node = new TNode<int, float>(_Key, _data, pFirst);
    node->pNext = pFirst;
    if (pCurr == pFirst)
        pPrev = node;
    pFirst = node;

};

void TList<int, float>::InsertToEnd(int _Key, float _data)
{
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;
    TNode<int, float>* curr = pCurr;

    Reset();
    while (pNext)
        Next();

    TNode<int, float>* node = new TNode<int, float>(_Key, _data);

    if (!pFirst)
    {
        pFirst = node;
    }
    else
        pCurr->pNext = node;

    if (curr == pCurr)
        pNext = node;
    else
        pNext = next;

    pCurr = curr;
    pPrev = prev;
};

void TList<int, float>::InsertAfter(int _Key, int newKey, float _data)
{
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;
    TNode<int, float>* curr = pCurr;

    Reset();

    TNode<int, float>* node = Search(_Key);
    if (node == nullptr)
        throw Exception_errors("  Key didn't find");

    while (pCurr != node)
        Next();

    TNode<int, float>* _node = new TNode<int, float>(newKey, _data);
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

void TList<int, float>::InsertBefore(int _Key, int newKey, float _data)
{
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;
    TNode<int, float>* curr = pCurr;

    Reset();

    if ((IsEnded()) || (pFirst->Key == _Key))
    {
        InsertToStart(newKey, _data);
        pCurr = pFirst;
        return;
    }

    TNode<int, float>* node = Search(_Key);
    if (node == nullptr)
    {
        throw Exception_errors("  Key didn't find");
        return;
    }

    while (pCurr != node)
        Next();
    TNode<int, float>* _node = new TNode<int, float>(newKey, _data, pCurr);
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

void TList<int, float>::Remove(int _Key)
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

        TNode<int, float>* node = pFirst;
        pFirst = pFirst->pNext;
        delete node;

        return;
    }

    TNode<int, float>* curr = pCurr;
    TNode<int, float>* prev = pPrev;
    TNode<int, float>* next = pNext;

    Reset();
    TNode<int, float>* node = Search(_Key);

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

TNode<int, float>* TList<int, float>::GetpFirst() const
{
    return pFirst;
};

TNode<int, float>* TList<int, float>::GetpCurr() const
{
    return pCurr;
};

TNode<int, float>* TList<int, float>::GetpPrev() const
{
    return pPrev;
};

void TList<int, float>::Reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
    if (pFirst)
        pNext = pCurr->pNext;
    else
        pNext = nullptr;
};

bool TList<int, float>::IsEnded() const
{
    if (pCurr == nullptr)
        return true;
    return false;
};

void TList<int, float>::Next()
{
    pPrev = pCurr;
    pCurr = pNext;

    if (pCurr)
        pNext = pCurr->pNext;
    else
        pNext = nullptr;;
};

#endif