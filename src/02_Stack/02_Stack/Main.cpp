#include "Stack.h"
#include "Postfix.h"
#include "Exception.h"
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

void main()
{
    float amount = 0;
    string strUser;
    string post;
    string Letters;

    cout << "  +------------------------------------+\n";
    cout << "  |\t      -POSTFIX NOTATION-       |\n";
    cout << "  +------------------------------------+\n";
    cout << "\n  Enter the arithmetick string: ";
    getline(cin, strUser);
	try
	{
		post = Postfix::PostfixForm(strUser);
	}
	catch (Exception_errors& e)
	{
		cerr << e.what() << endl;
	};
	cout << "\n  Postfix Form: " << post << endl;

    int c = Postfix::Count(post);
    float* Numbers = new float[c];
    Postfix::Value(Letters, Numbers, post, c);
 
    try
    {
        amount = Postfix::CountingValue(post, Letters, Numbers);
        cout << "  Result = " << amount;
    }
    catch(Exception_errors& e)
    {
        cerr << e.what() << endl;
    };
    cin.get();
}