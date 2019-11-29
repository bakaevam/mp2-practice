#include "Includes\Exception.h"
#include "Includes\TPost.h"
#include "Includes\TList.h"
#include <iostream>
using namespace std;

int main()
{
    //// Test PostfixForm ////
    char type;
    char ch1 = 'a';
    char ch2 = 'l';
    cout << endl << "\t--Postfix Form Test--" << endl;

    do {
        cout << "  Enter type of stack (a = Array, l = List): ";
		type = getchar();
		getchar();
    } while ((type != ch1) && (type != ch2));

    try
    {
        if (type == 'a')
        {
            TPost<float> str(Array);
            float res = str.UserStr();
			cout << "\n  Result: " << res;
        }
		else if (type == 'l')
		{
			TPost<float> str(List);
			float res = str.UserStr();
			cout << "\n  Result: " << res;
		}
    }
    catch (Exception_errors& e)
    {
        cerr << e.what() << endl;
    }

    cin.get();
}