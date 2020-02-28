#ifndef _DHEAP_H_
#define _DHEAP_H_

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
	~TDHeap();

	void Swap(int a, int b);
	int MinChild(int a);
	void SiftUp(int a);
	void SiftDown(int a);
	void DeleteMin();
	void Hilling();

	friend ostream& operator<<(ostream& os, TPolinom& tmp)
	{
		os << " d = " << d << endl;;

		for (int i = 0; i < size; i++)
			os << " " << elements[i];  
		return os;
	}
};

#endif

