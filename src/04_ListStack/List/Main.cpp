#include "TStack.h"
#include <iostream>
using namespace std;

void main()
{
    cout << "\t--List Test--" << endl;

    TList<int, int> L1;
    int a[1] = { 2 };
	L1.InsertToStart(2, a);
    L1.InsertToEnd(3, a);

    TList<int, int>L2(L1); // Тест конструктора копирования

    cout << "\n  List 1: ";
    L1.Print();
    cout << "\n  List 2: ";
    L2.Print();

    cout << "  Find the element with key 2: " << L2.Search(2) << endl;

    L1.InsertAfter(3, 4, a);
    cout << "  Insert after key 3: ";
    L1.Print();

    L2.InsertBefore(2, 1, a);
    cout << "  Insert before key 2: ";
    L2.Print();

    cin.get();
}