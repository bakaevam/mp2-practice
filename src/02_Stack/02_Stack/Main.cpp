#include "Stack.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

void main()
{
    int S = 0;
    float amount = 0;
    char* strUser = new char[100];
    cout << " Enter the arithmetick string: ";
    cin.getline(strUser, 100);
    char tmp[25];
    char* post = PostfixForm(strUser, S);
    for(int i = 0; i < S; i++)
        tmp[i] = post[i]; 
    try
    {
        amount = CountingValue(tmp, S);
    }
    catch(Exception_errors& e)
    {
        cerr << e.what() << endl;
    };
    cout << "\n  Result = " << amount;
    cin.get();
}