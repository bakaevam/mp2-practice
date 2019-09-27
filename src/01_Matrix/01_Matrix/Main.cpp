#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <ctime>
using namespace std;

void main()
{
    TMatrix<int> m1(5), m2(5), m3(3);
    TVector<int> v1(5, 0), v2(5, 0), v3(3, 0);
    int i = 0, j = 0;
    srand((unsigned int)time(NULL));

    cout << "    -Vector TEST- \n" << endl;
        for (i = 0; i < v1.GetSize(); i++)
        {
            v1[i] = rand() % 9 + 1;
            v2[i] = rand() % 9 + 1;
        }
        for (i = 0; i < v3.GetSize(); i++)
            v3[i] = rand() % 9 + 1;


    cout << "  a = " << v1 << endl;
    cout << "  b = " << v2 << endl;
    cout << "  c = " << v3 << endl;
    cout << "\n  a * 2 = " << (v1 * 2) << endl;
    cout << "\n  a + 2 = " << (v1 + 2) << endl;
    cout << "\n  a - 2 = " << (v1 - 2) << endl;
    cout << "\n  a * b = " << (v1 * v2) << endl;
    cout << "\n  a - b = " << (v1 - v2) << endl;
    cout << "\n  a + b = " << (v1 + v2) << endl;
    cout << "\n  |a| = " << v1.Length() << endl;
    try
    {
        cout << "\n  a * c = ";
        cout << (v1 * v3) << endl;
    }
    catch (Exception_sizes& e)
    {
        cerr << e.what() << endl;
    }
    try
    {
        cout << "\n  a + c = ";
        cout << (v1 + v3) << endl;
    }
    catch (Exception_sizes& e)
    {
        cerr << e.what() << endl;
    }

    cout << "\n\n    -Triangular Matrix TEST- \n" << endl;
    for (i = 0; i < m1.GetSize(); i++)
        for (j = 0; j < m1.GetSize() - i; j++)
        {
            m1[i][j] = rand() % 9 + 1;
            m2[i][j] = rand() % 9 + 1;
        };
    for (i = 0; i < m3.GetSize(); i++)
        for (j = 0; j < m3.GetSize() - i; j++)
        {
            m3[i][j] = rand() % 9 + 1;
        };
    cout << "  A = \n" << m1 << endl;
    cout << "  B = \n" << m2 << endl;
    cout << "  C = \n" << m3 << endl;

    cout << "\n  A * 2 = " << (m1 * 2) << endl;
    cout << "\n  A + 2 = " << (m1 + 2) << endl;
    cout << "\n  A - 2 = " << (m1 - 2) << endl;
    cout << "\n  A * B = " << (m1 * m2) << endl;
    cout << "\n  A - B = " << (m1 - m2) << endl;
    cout << "\n  A + B = " << (m1 + m2) << endl;
    cout << "\n  A * a = " << (m1 * v1) << endl;

    try
    {
        cout << "\n  A + C = ";
        cout << (m1 + m3) << endl;
    }
    catch (Exception_sizes& e)
    {
        cerr << e.what() << endl;
    }

    try
    {
        cout << "\n  A * C = ";
        cout << (m1 * m3) << endl;
    }
    catch (Exception_sizes& e)
    {
        cerr << e.what() << endl;
    }

    try
    {
        cout << "\n  A * c = ";
        cout << (m1 * v3) << endl;
    }
    catch (Exception_sizes& e)
    {
        cerr << e.what() << endl;
    }

    cin.get();
}