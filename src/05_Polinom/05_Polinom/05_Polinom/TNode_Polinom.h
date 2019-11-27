#ifndef _TNODE_POLINOM_H_
#define _TNODE_POLINOM_H_
#include "TNode.h"
#include "Exception.h"

template<>
class TNode<int, float>
{
public:
    int Key;
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
};

#endif