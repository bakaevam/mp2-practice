#ifndef _DHEAP_H_
#define _DHEAP_H_
#include "Edge.h"
#include <iostream>
#include <math.h>
using namespace std;

template<class T>
class TDHeap
{
private:
	int max_size;
	int size;
	int d;
	T* elements;
public:
	TDHeap();
	TDHeap(int newMaxSize, int newD, T* newElements, int n);
	TDHeap(const TDHeap&);
	~TDHeap();

	void Swap(int a, int b);
	int MinChild(int a);
	void SiftUp(int a);
	void SiftDown(int a);
	void DeleteMin();
	void Hilling();
	int GetSize() const;
	T* GetElements() const;
	void ChangeSize(int a);

	template<class T>
	friend ostream& operator<<(ostream& os, TDHeap& tmp);
};

template<class T>
TDHeap<T>::TDHeap()
{
	max_size = 20;
	size = 0;
	d = 0;
};

template<class T>
TDHeap<T>::TDHeap(int newMaxSize, int newD, T* newElements, int n)
{
	if (n > newMaxSize)
		return;

	max_size = newMaxSize;
	d = newD;
	size = n;
	
	elements = newElements;
};

template<class T>
TDHeap<T>::TDHeap(const TDHeap& tmp)
{
	max_size = tmp.max_size;
	size = tmp.size;
	d = tmp.d;
	
	elements = tmp.elements;
};

template<class T>
TDHeap<T>::~TDHeap()
{
	max_size = 0;
	elements = nullptr;
	size = 0;
	d = 0;
};

template<class T>
void TDHeap<T>::Swap(int a, int b)
{
	T tmp = elements[a];
	elements[a] = elements[b];
	elements[b] = tmp;
};

template<class T>
void TDHeap<T>::SiftUp(int a)
{
	int parent = (a - 1) / d;
	while (a > 0)
	{
		if (elements[parent] > elements[a])
		{
			Swap(parent, a);
			a = parent;
		}
		else break;
	}
};

template<class T>
int TDHeap<T>::MinChild(int a)
{
	//Если a - это лист
	if ((a * d + 1) >= size)
		return -1;

	int c1 = a * d + 1;
	int c2 = fmin(size - 1, a * d + d);
	int c = c1;

	for (int i = c1; i <= c2; i++)
		if (elements[i] < elements[c])
			c = i;

	return c;
};

template<class T>
void TDHeap<T>::SiftDown(int a)
{
	int c = MinChild(a);
	while ((c != -1) && (elements[c] < elements[a]))
	{
		Swap(c, a);
		a = c;
		c = MinChild(a);
	}
};

template<class T>
void TDHeap<T>::DeleteMin()
{
	Swap(0, size - 1);
	size--;
	SiftDown(0);
};

template<class T>
void TDHeap<T>::Hilling()
{
	for (int i = size - 1; i >= 0; i--)
		SiftDown(i);
};

template<class T>
ostream& operator<<(ostream& os, TDHeap<T>& tmp)
{
	os << endl;
	for (int i = 0; i < tmp.GetSize(); i++)
		os << " " << tmp.GetElements()[i];
	return os;
};

template<class T>
int TDHeap<T>::GetSize() const
{
	return size;
};

template<class T>
T* TDHeap<T>::GetElements() const
{
	return elements;
};

template<class T>
void TDHeap<T>::ChangeSize(int a)
{
	size += a;
};

#endif

