#ifndef _POSTFIX_H_
#define _POSTFIX_H_
#include "Stack.h"
#include <string>

class Postfix
{private:
	static bool SignComparison(char, Stack<char>&);
	static int Priority(char);
public:
	static int Count(string);
    static string PostfixForm(string);
    static void Value(string&, float* Numbers, string, int);
    static float CountingValue(string, string, float*);
};
#endif

