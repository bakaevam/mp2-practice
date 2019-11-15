#include "TList.h"
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
	cout << L1;
    cout << "  List 2: ";
	cout << L2;

    cout << endl << "  Find the element with key 2: " << L2.Search(2) << endl;
	cout << endl << "  Find the element with key 25: " << L2.Search(25) << endl;


    L1.InsertAfter(3, 4, a);
    cout << "  Insert after key 3: ";
	cout << L1;
	try
	{
		cout << "  Insert after key 25: ";
		L1.InsertAfter(25, 4, a);
		cout << L1;
	}
	catch (Exception_errors& e)
	{
		cerr << e.what() << endl;
	};

    L2.InsertBefore(2, 1, a);
    cout << "  Insert before key 2: ";
	cout << L2;

    L2.InsertBefore(3, 10, a);
    cout << "  Insert before key 3: ";
	cout << L2;

    L2.Remove(10);
    cout << "  Delete the elemtnt with key 10: ";
	cout << L2;

    cin.get();
}