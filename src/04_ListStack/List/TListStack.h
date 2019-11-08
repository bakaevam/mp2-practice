#ifndef  _TLISTSTACK_H_
#define _TLISTSTACK_H_
#include "TList.h"

template<class TKey, class TData>
class TListStack: public TStack
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
TListStack<TKey, TData>::~TListStack<TKey, TData>()
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
