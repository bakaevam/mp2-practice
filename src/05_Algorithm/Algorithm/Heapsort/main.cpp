#include <iostream>
#include "../Heap_Set_Library/DHeap.h"
#include "Heapsort.h"
#include <ctime>
#include <conio.h>
#include <stdlib.h>
using namespace std;

void main()
{
	int* a = new int[5];
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++)
	{
		a[i] = rand() % 10;
	}

	//Вывод нового массива
	for (int i = 0; i < 5; i++)
		cout << " " << a[i];

	Heapsort<int>::HeapSort(a, 5);
	
	//Вывод отсортированного массива
	for(int i = 0; i < 5; i++)
		cout << " " << a[i];
}
