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
    TNode(TKey, TData*, TNode* node = nullptr);
    ~TNode();
};
//////////////////////////////////////////////////////////
template<class TKey, class TData>
TNode<TKey, TData>::TNode()
{
    Key = 0;
    data = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data, TNode<TKey, TData>* node)
{
    Key = _key;
    data = _data;
    pNext = node;
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

#endif
