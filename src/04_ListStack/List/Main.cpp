#include "TStack.h"
#include "TPost.h"
#include <iostream>
using namespace std;

void main()
{
    //// Test PostfixForm ////
    cout << endl << "\t--Postfix Form Test--" << endl;

    cout << "  Enter type of stack (a = Array, l = List): ";
    string type;
    getline(cin, type);

    try
    {
        if (type[0] == 'a')
        {
            TPost<float> str(Array);
            float res = str.UserStr();
            cout << res;
        };
    }
    catch (Exception_errors& e)
    {
        cerr << e.what() << endl;
    };

    try
    {
        if (type[0] == 'l')
        {
            TPost<float> str(List);
            float res = str.UserStr();
            cout << "\n  Result: " << res;
        };
    }
    catch (Exception_errors& e)
    {
        cerr << e.what() << endl;
    };

    cin.get();
};