#include "TPolinom.h"
#include "TList_Polinom.h"
#include <iostream>
#include <conio.h>
using namespace std;

void main()
{
    string s1 = "3x^2yz^6";
    string s2 = "yz^6+x^2yz^6";
    string s3 = "5y^3z^6 + z - 4yz^6";
    TList<int, float>* l1 = new TList<int, float>();

    l1->InsertToStart(36, 5);
    l1->InsertToEnd(0, 2);
    l1->InsertToEnd(16, -4);

    TPolinom p1;
    TPolinom p2(s2);
    TPolinom p3(s3);
    cout << p1 << endl;
    cout << p2 << endl;
    cout << p3;
    p3.StandartView();
    cout << p3;
    cin.get();
}