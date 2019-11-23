#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
#include <exception>
#include <string>
#include <iostream>
using namespace std;

class Exception_errors : exception
{
private:
    const string mes;
public:
    Exception_errors(string e)
        :mes(e)
    {
    }
    const char* what() const { return mes.c_str(); }
};
#endif