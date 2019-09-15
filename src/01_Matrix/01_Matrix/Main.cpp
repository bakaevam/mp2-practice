#include <iostream>
#include <conio.h>
#include <iomanip>
#include "Matrix.h"
using namespace std;

void main()
{
    cout << "123" << endl;
    TMatrix<int> m1(5), m2(5), m3(5);
    TVector<int> v1(5, 0), v2(2, 0), v3(2, 0);
    int i, j;

    cout << "    -Triangular Matrix TEST- " << endl;
   /* for (i = 0; i < 5; i++)
        for (j = i; j < 5; j++)
        {
            m1[i][j] = i * 10 + j;
            m2[i][j] = (i * 10 + j) * 100;
        };
    cout << m1 << endl;*/
    cin.get();
}