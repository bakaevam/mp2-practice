#ifndef _TNODE_H_
#define _TNODE_H_
#include <iostream>
using namespace std;

template<class TKey, class TData>
class TNode
{
public:
    TKey Key;
    TData* data;
    TNode<TKey, TData>* pNext;

    TNode();
    TNode(const TNode&);
    TNode(TKey, TData*);
    ~TNode();

    void Output();
};
//////////////////////////////////////////////////////////
template<class TKey, class TData>
TNode<TKey, TData>::TNode()
{
    Key = nullptr;
    data = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data)
{
    Key = _key;
    data = _data;
    pNext = nullptr;
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& tmp)
{
    Key = tmp.Key;
    pNext = nullptr;
    data = tmp.data;
};

template<class TKey, class TData>
TNode<TKey, TData>::~TNode()
{
    Key = 0;
    data = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
void TNode<TKey, TData>::Output()
{
    cout << " \n" << this->Key;
    cout << " \n   |\n";
}
#endif
