#include <iostream>
#include "DHeap.h"
using namespace std;

void main()
{
	int a[5] = {1, 10, 9, 8, 2};
	TDHeap<int> heap1(10, 3, a, 5);

	cout << heap1;
}
