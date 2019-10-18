#ifndef _POSTFIX_H_
#define _POSTFIX_H_
#include "Stack.h"
#include <string>

class Postfix
{
public:
    static int Priority(char);
    static bool SignComparison(char, Stack<char>&);
    static string PostfixForm(string);
    static int Count(string);
    static void Value(string&, float* Numbers, string, int);
    static float CountingValue(string, string, float*);
};
#endif

