#ifndef _TPOST_H_
#define _TPOST_H_
#include "TStack.h"
#include <string>
#include <stdio.h>

template<class ValType>
class TPost
{
private:
    TStack<ValType> Operands;
    TStack<ValType> Signs;
    TStack<ValType> Value;

    enum StackType
    {
        Array,
        List,
    };

    bool SignComparison(char, TStack<char>&);
    int Priority(char);
public:
    TPost();
    TPost(StackType);
    ~TPost();

    void UserStr();
    int Count(string);
    string PostfixForm(string);
    void Value(string&, float* Numbers, string, int);
    float CountingValue(string, string, float*);
};

template<class ValType>
TPost<ValType>::TPost()
{
   /* Operands = new TStack;
    Signs = new TStack;
    Value = new TStack;*/
}

template<class ValType>
TPost<ValType>::TPost(StackType type)
{
    if (type == a)
    {
        Operands = new TArrayStack;
        Signs = new TArrayStack;
        Value = new TArrayStack;
    };
    if (type == l)
    {
        Operands = new TListStack;
        Signs = new TListStack;
        Value = new TListStack;
    };

    throw "  Stack Type isn't correct";
}

template<class ValType>
TPost<ValType>::~TPost()
{
    delete Operands;
    delete Signs;
    delete Value;
}

template<class ValType>
ValType TPost<ValType>::UserStr()
{
    cout << "  Enter type of stack (a = Array, l = list): ";
    string StackType = nullptr;
    getline(cin, StackType);

    if ((StackType != a) && (StackType != l))
        throw "  Stack Type isn't correct";

    string strUser = nullptr;
    cout << "\n  Enter the arithmetic string: ";
    getline(cin, strUser);
    string post = PostfixForm(strUser);

    int c = Count(post);
    float* Numbers = new float[c];
    string Letters = nullptr;
    Value(Letters, Numbers, post, c);
    float amount = CountingValue(post, Letters, Numbers);
    cout << "\n  Result: " << amount;
};

template<class ValType>
int TPost::Priority(char sign)
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
bool TPost::SignComparison(char tmp, TStack<char>& _sign)
{
    
    if (Priority(_sign.TopPop()) < Priority(tmp))
        return true;

    return false;
};

template<class ValType>
string TPost::PostfixForm(string exp)
{
    Signs(exp.length() + 1);
    Operands(exp.length() + 1);
    char _size = exp.length();

    for (int i = 0; i < exp.length(); i++)
    {
        
        if ((exp[i] == '*') || (exp[i] == '/') ||
            (exp[i] == '+') || (exp[i] == '-'))
        {
            
            if (exp[i] == ' ')
                continue;
            if (Sign.IsEmpty())
            {
                Signs.Push(exp[i]);
                continue;
            }

            if (SignComparison(exp[i], Signs)) 
            {
                while (!Signs.IsEmpty())
                {
                    Operands.Push(Signs.TopPop());
                    Signs.Pop();
                }
                Signs.Push(exp[i]);
            }
            else
                Signs.Push(exp[i]);
        }

        if (exp[i] == '(')
            Signs.Push(exp[i]);

        
        if (isalpha(exp[i]))
            Operands.Push(exp[i]);

        
        if (exp[i] == ')')
        {
            int flag = 0;
            while (!Signs.IsEmpty())
            {
                if (Signs.TopPop() != '(')
                {
                    Operands.Push(Signs.TopPop());
                    Signs.Pop();
                    continue;
                }
                Signs.Pop();
                flag = 1;
                break;
            };
            if ((Signs.IsEmpty()) && (flag != 1))
                throw Exception_errors("  Didn't find '('");
        };
    };

    
    while (!Signs.IsEmpty())
    {
        Operands.Push(Signs.TopPop());
        Signs.Pop();
    }
    string tmp;
    while (!Operands.IsEmpty())
    {
        tmp += Operands.TopPop();
        Operands.Pop();
    }

    for (int i = 0; i < tmp.length() / 2; i++)
        swap(tmp[i], tmp[tmp.length() - 1 - i]);

    return tmp;
};

template<class ValType>
int TPost::Count(string PostForm)
{
    int count = 0;
    for (int i = 0; i < PostForm.length(); i++)
        if (isalpha(PostForm[i]))
            count++;
    return count;
}

template<class ValType>
void TPost::Value(string& Letters, float* Numbers, string PostForm, int count)
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
float TPost::CountingValue(string PostForm, string Letters, float* Numbers)
{
    Value(25);

    
    for (int i = 0; i < PostForm.length(); i++)
    {
        if (isalpha(PostForm[i]))
            for (int j = 0; j < Letters.length(); j++)
                if (Letters[j] == PostForm[i])
                {
                    Value.Push(Numbers[j]);
                    break;
                }
        if ((PostForm[i] == '*') || (PostForm[i] == '/') ||
            (PostForm[i] == '+') || (PostForm[i] == '-'))
        {
            float a = Value.TopPop();
            Value.Pop();
            float b = Value.TopPop();
            Value.Pop();

            if (PostForm[i] == '*') Value.Push(b * a);
            if (PostForm[i] == '/')
            {
                if (a == 0)
                    throw  Exception_errors("\n  Cannot be divided by 0");
                else Value.Push(b / a);
            };
            if (PostForm[i] == '+') Value.Push(b + a);
            if (PostForm[i] == '-') Value.Push(b - a);
        }
    }
    return Value.TopPop();
};
#endif