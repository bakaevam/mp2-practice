#ifndef _NODE_H_
#define _NODE_H_

template<class TKey, class TData>
class TNode
{
public:
    TKey Key;
    TData* data;
    TNode<TKey, TData>* pNext;

    TNode();
    TNode(const TNode&);
    TNode(TKey, TData*, TNode*);
    ~TNode();
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode()
{
    Key = nullptr;
    data = nullptr;
    pNext = nullptr;
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _data, TNode* _node)
{
    Key = _key;
    data = new (_data);
    pNext = _node;
};

template<class TKey, class TData>
TNode<TKey, TData>::TNode(const TNode& tmp)
{
    Key = tmp.Key;
    pNext = tmp.pNext;
    data = tmp.data;
};

template<class TKey, class TData>
TNode<TKey, TData>::~TNode()
{
    Key = 0;
    delete[] data;
    pNext = nullptr;
};
#endif
