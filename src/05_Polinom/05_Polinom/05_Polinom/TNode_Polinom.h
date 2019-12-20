#ifndef _TNODE_POLINOM_H_
#define _TNODE_POLINOM_H_
#include "TNode.h"
#include "Exception.h"

template<>
class TNode<int, float>
{
public:
    unsigned int Key;
    float data;
    TNode<int, float>* pNext;

    TNode(): Key(0), data(0), pNext(nullptr) {}
    TNode(const TNode& tmp) : Key(tmp.Key), data(tmp.data), pNext(tmp.pNext) {};
    TNode(int k, float d, TNode* node = nullptr) : Key(k), data(d), pNext(node) {};
    ~TNode()
    {
        Key = 0;
        data = 0;
        pNext = nullptr;
    };

    bool operator!=(const TNode&) const;
    bool operator==(const TNode&) const;
    bool operator<=(const TNode&) const;

    TNode<int, float>* operator*(const TNode&);
};


bool TNode<int, float>::operator!=(const TNode& tmp) const
{
    return (!(*this == tmp));
};

bool TNode<int, float>::operator==(const TNode& tmp) const
{
    return ((this->Key == tmp.Key) && (this->data == tmp.data));
};

bool TNode<int, float>::operator<=(const TNode& tmp) const
{
    return (this->Key <= tmp.Key);
};

TNode<int, float>* TNode<int, float>::operator*(const TNode& tmp)
{
    TNode<int, float>* res = new TNode<int, float>();

    int degX = tmp.Key / 100;
    int degY = (tmp.Key % 100) / 10;
    int degZ = tmp.Key % 10;

    int _degX = Key / 100;
    int _degY = (Key % 100) / 10;
    int _degZ = Key % 10;

    if ((degX + _degX > 9) || ((degY + _degY > 9) || (degZ + _degZ > 9)))
    {
        throw Exception_errors("  Degree shouldn't exceed 9");
    };

    res->Key = Key + tmp.Key;
    res->data = data * tmp.data;

    return res;
};
#endif