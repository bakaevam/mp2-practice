#include "TPolinom.h"
#include "TList_Polinom.h"
#include "Exception.h"
#include <iostream>
#include <conio.h>
using namespace std;

void main()
{
    string s1 = "7z^6 + 3x^2yz^6 - 11x + 2xy + 8y^5z";
    string s2 = "yz^6 + x^2yz^6";
    string s3 = "z^2 + y";
    TList<int, float>* l1 = new TList<int, float>();

    l1->InsertToStart(36, 5);
    l1->InsertToEnd(0, 2);
    l1->InsertToEnd(16, -4);
    l1->InsertToEnd(100, -11);
    l1->InsertToEnd(50, -4);

    TPolinom p1(s1);
    TPolinom p2(p1);
    TPolinom p3(l1);
    TPolinom p4(s3);

    try
    {
        cout << "\t -POLINOM TEST-\n" << endl;
        cout << "  Polinom from string: p1 =" << p1 << endl;
        cout << "  Polinom as copy p1: p2 =" << p2 << endl;
        cout << "  Polinom from list: p3 =" << p3 << endl;
        cout << "  Polinom from string: p4 =" << p4 << endl;
        cout << "  p1 + p2 =" << p1 + p2 << endl;
        cout << "  p1 - p3 =" << p1 - p3 << endl;
        cout << "  p1 * p3 =";
        cout << p1 * p3 << endl;
    }
    catch (Exception_errors& e)
    {
        cerr << e.what() << endl;
    }
    cout << endl << "  p1 * p4 =" << p1 * p4 << endl;
    cin.get();
}