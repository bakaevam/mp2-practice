#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_
#include "../Heap_Set_Library/DHeap.h"

template<class T>
class Heapsort
{
public:
	static void HeapSort(T*&, int n);
};

template<class T>
void Heapsort<T>::HeapSort(T*& a, int n)
{
	TDHeap<int> heap(10, 2, a, n);
	heap.Hilling();

	for(int i = (n - 1); i >= 0; i--)
	{
		heap.Swap(heap.GetSize() - 1, 0);
		heap.ChangeSize(-1);
		heap.SiftDown(0);
	};

	cout << heap;
	for (int i = 0; i < n; i++)
		a[i] = heap.GetElements()[i];
};

#endif
