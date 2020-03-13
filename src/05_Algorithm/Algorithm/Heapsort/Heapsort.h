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
	TDHeap<float> heap(10, 2, a, n);
	heap.Hilling();

	for(int i = 0; i < n; i++)
		heap.DeleteMin();

	for (int i = 0; i < n; i++)
		a[i] = heap.GetElements()[i];
};

#endif
