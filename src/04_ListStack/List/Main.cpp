#include "List.h"
#include <iostream>
using namespace std;

void main()
{
	TList<int, int> L1;
	int a[2] = { 1, 2 };
	L1.InsertToStart(2, a);
}