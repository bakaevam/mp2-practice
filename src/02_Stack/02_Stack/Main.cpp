#include "Stack.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

void main()
{
    int S = 0;
    char* strUser = new char[100];
    cout << " Enter the arithmetick string: ";
    cin.getline(strUser, 100);
    cout << strUser;
    int amount = CountingValue(PostfixForm(strUser, S), S);
    cout << "\n  Result = " << amount;
    cin.get();
}