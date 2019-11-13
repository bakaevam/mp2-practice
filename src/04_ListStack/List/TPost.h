#ifndef _TPOST_H_
#define _TPOST_H_
#include "TStack.h"
#include "Exception.h"
#include <string>
#include <iostream>
#include <stdio.h>
using namespace std;

template<class ValType>
class TPost
{
private:
    TStack<char>* Operands;
    TStack<char>* Signs;
    TStack<float>* Value;

    bool SignComparison(char, TStack<char>&);
    int Priority(char);
    int Count(string);
public:
    TPost(StackType);

    ValType UserStr();
    string PostfixForm(string);
    void Values(string&, float*, string, int);
    float CountingValue(string, string, float*);
};

template<class ValType>
TPost<ValType>::TPost(StackType type)
{
    Operands = TStack<char>::Create(type);
    Signs = TStack<char>::Create(type);
    Value = TStack<float>::Create(type);
}

template<class ValType>
ValType TPost<ValType>::UserStr()
{
    string strUser;
    cout << "\n  Enter the arithmetic string: ";
    getline(cin, strUser);
    string post = PostfixForm(strUser);

    cout << "  Postfix form: " << post << endl;

    int c = Count(post);
    float* Numbers = new float[c];
    string Letters;
    Values(Letters, Numbers, post, c);
    float amount = CountingValue(post, Letters, Numbers);
    return amount;
};

template<class ValType>
int TPost<ValType>::Priority(char sign)
{
    switch (sign)
    {
    case '*': return 1;
    case '/': return 1;
    case '+': return 2;
    case '-': return 2;
    default: return 3;
    }
}

template<class ValType>
bool TPost<ValType>::SignComparison(char tmp, TStack<char>& _sign)
{
    
    if (Priority(_sign.TopPop()) < Priority(tmp))
        return true;

    return false;
};

template<class ValType>
string TPost<ValType>::PostfixForm(string exp)
{
    char _size = exp.length();

    for (int i = 0; i < exp.length(); i++)
    {
        
        if ((exp[i] == '*') || (exp[i] == '/') ||
            (exp[i] == '+') || (exp[i] == '-'))
        {
            
            if (exp[i] == ' ')
                continue;
            if (Signs->IsEmpty())
            {
                Signs->Push(exp[i]);
                continue;
            }

            if (SignComparison(exp[i], *Signs)) 
            {
                while (!Signs->IsEmpty())
                {
                    Operands->Push(Signs->TopPop());
                    Signs->Pop();
                }
                Signs->Push(exp[i]);
            }
            else
                Signs->Push(exp[i]);
        }

        if (exp[i] == '(')
            Signs->Push(exp[i]);

        
        if (isalpha(exp[i]))
            Operands->Push(exp[i]);

        
        if (exp[i] == ')')
        {
            int flag = 0;
            while (!Signs->IsEmpty())
            {
                if (Signs->TopPop() != '(')
                {
                    Operands->Push(Signs->TopPop());
                    Signs->Pop();
                    continue;
                }
                Signs->Pop();
                flag = 1;
                break;
            };
            if ((Signs->IsEmpty()) && (flag != 1))
                throw Exception_errors("  Didn't find '('");
        };
    };

    
    while (!Signs->IsEmpty())
    {
        Operands->Push(Signs->TopPop());
        Signs->Pop();
    }
    string tmp;
    while (!Operands->IsEmpty())
    {
        tmp += Operands->TopPop();
        Operands->Pop();
    }

    for (int i = 0; i < tmp.length() / 2; i++)
        swap(tmp[i], tmp[tmp.length() - 1 - i]);

    return tmp;
};

template<class ValType>
int TPost<ValType>::Count(string PostForm)
{
    int count = 0;
    for (int i = 0; i < PostForm.length(); i++)
        if (isalpha(PostForm[i]))
            count++;
    return count;
};

template<class ValType>
void TPost<ValType>::Values(string& Letters, float* Numbers, string PostForm, int count)
{
    int topLetters = 0;
    float val = 0;
    char* letters = new char[count];
    float* numbers = new float[count];
    
    for (int i = 0; i < PostForm.length(); i++)
        if (isalpha(PostForm[i]))
        {
            int flag = 0;
            for (int j = 0; j < topLetters; j++)
                if (letters[j] == PostForm[i])
                {
                    flag = 1;
                    break;
                }
            if (flag == 0)
            {
                letters[topLetters] = PostForm[i];
                cout << "\n  " << letters[topLetters] << " = ";
                cin >> val;
                numbers[topLetters++] = val;
            }
        }
    Letters.assign(letters);
    memcpy(Numbers, numbers, sizeof(float) * count);
};

template<class ValType>
float TPost<ValType>::CountingValue(string PostForm, string Letters, float* Numbers)
{
    //Value(25);

    for (int i = 0; i < PostForm.length(); i++)
    {
        if (isalpha(PostForm[i]))
            for (int j = 0; j < Letters.length(); j++)
                if (Letters[j] == PostForm[i])
                {
                    Value->Push(Numbers[j]);
                    break;
                }
        if ((PostForm[i] == '*') || (PostForm[i] == '/') ||
            (PostForm[i] == '+') || (PostForm[i] == '-'))
        {
            float a = Value->TopPop();
            Value->Pop();
            float b = Value->TopPop();
            Value->Pop();

            if (PostForm[i] == '*') Value->Push(b * a);
            if (PostForm[i] == '/')
            {
                if (a == 0)
                    throw  Exception_errors("\n  Cannot be divided by 0");
                else Value->Push(b / a);
            };
            if (PostForm[i] == '+') Value->Push(b + a);
            if (PostForm[i] == '-') Value->Push(b - a);
        }
    }
    return Value->TopPop();
};
#endif