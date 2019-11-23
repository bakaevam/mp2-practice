#ifndef  _TSTACK_H_
#define _TSTACK_H_
#include "TArrayStack.h"
#include "TListStack.h"

template<class ValType> class TArrayStack;
template<class ValType> class TListStack;

enum StackType
{
    Array,
    List,
};

template<class ValType>
class TStack
{
public:
    static TStack* Create(StackType);

    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual void Push(ValType) = 0;
    virtual void Pop() = 0;
    virtual ValType TopPop() const = 0;
};

/////  IMPLEMENTATION TSTACK/////

template<class ValType>
TStack<ValType>* TStack<ValType>::Create(StackType type)
{
    if (type == Array)
    {
        return new TArrayStack<ValType>(100);
    }
    if (type == List)
    {
        return new TListStack<ValType>();
    }
    throw Exception_errors(" Stack Type isn't correct");
};

#endif

