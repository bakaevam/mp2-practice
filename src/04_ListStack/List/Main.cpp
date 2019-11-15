#include "TStack.h"
#include "TPost.h"
#include "Exception.h"
#include <iostream>
using namespace std;

void main()
{
    //// Test PostfixForm ////
    string type;
    string ch1 = "a";
    string ch2 = "l";
    cout << endl << "\t--Postfix Form Test--" << endl;

    do {
        cout << "  Enter type of stack (a = Array, l = List): ";
        getline(cin, type);
    } while ((type != ch1) && (type != ch2));

    try
    {
        if (type[0] == 'a')
        {
            TPost<float> str(Array);
            float res = str.UserStr();
			cout << "\n  Result: " << res;
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