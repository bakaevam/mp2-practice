#include <iostream>
#include "../Heap_Set_Library/DHeap.h"
#include "../Heap_Set_Library/Heapsort.h"
#include <ctime>
#include <conio.h>
#include <stdlib.h>
using namespace std;

int main()
{
	int sizeArr = 0;
	int rangeA = 0;
	int rangeB = 0;
	srand((unsigned int)time(NULL));

	cout << "Enter size of array ";
	cin >> sizeArr; 

	cout << "Enter beginning of range ";
	cin >> rangeA;

	cout << "Enter ending of range ";
	cin >> rangeB;

	float* a = new float[sizeArr];

	for (int i = 0; i < sizeArr; i++)
	{
		a[i] = (float)(rand() % rangeB + rangeA);
	}

	//Вывод нового массива
	for (int i = 0; i < sizeArr; i++)
		cout << " " << a[i];

	cout << endl; 
	Heapsort<float>::HeapSort(a, sizeArr);
	
	//Вывод отсортированного массива
	for(int i = 0; i < sizeArr; i++)
		cout << " " << a[i];

	delete[] a;
}
