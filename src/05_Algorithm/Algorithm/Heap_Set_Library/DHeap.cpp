#include "pch.h"
#include "DHeap.h"
#include <math.h>

template<class T>
TDHeap<T>::TDHeap()
{
	max_size = 20;
	elements = new T(max_size);
	size = 0;
	d = 0;
};

template<class T>
TDHeap<T>::TDHeap(int newMaxSize, int newD, T* newElements, int n)
{
	max_size = newMaxSize;
	d = newD;
	memcpy(elements, newElements, sizeof(T) * n);
};

template<class T>
TDHeap<T>::~TDHeap()
{
	max_size = 0;
	delete elements;
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
	while (a > 0)
	{
		int parent = (a - 1) / d;
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
	//���� a - ��� ����
	if (a * d + 1 >= size)
		return -1;

	int c1 = a * d + 1;
	int c2 = fmin(n - 1, a * d + d);
	int c = c1;

	for (int i = c1; i < c2; i++)
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