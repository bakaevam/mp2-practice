#include "Stack.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

void main()
{
    char* post;
    int S = 0;
    float amount = 0;
    char* strUser = new char[100];

    cout << "  +------------------------------------+\n";
    cout << "  |\t      -POSTFIX NOTATION-       |\n";
    cout << "  +------------------------------------+\n";
    cout << "\n  Enter the arithmetick string: ";
    cin.getline(strUser, 100);
    char tmp[25];
	post = PostfixForm(strUser, S);

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