#include "Postfix.h"
#include "Stack.h"
#include "Exception.h"
#include <iostream>
#include <cstring>
using namespace std;

int Postfix::Priority(char sign)
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

bool Postfix::SignComparison(char tmp, Stack<char>& _sign)
{
    // true - перемещаем всё в другой стек
    //false - не перемещаем
    if (Priority(_sign.elem[_sign.top - 1]) < Priority(tmp))
        return true;
    else return false;
};

string Postfix::PostfixForm(string exp)
{
    Stack<char> Sign(exp.length() + 1),
        Operands(exp.length() + 1);
    char _size = exp.length();

    for (int i = 0; i < exp.length(); i++)
    {
        //Если пришел знак
        if ((exp[i] == '*') || (exp[i] == '/') ||
            (exp[i] == '+') || (exp[i] == '-'))
        {
            //Проверка на пробел
            if (exp[i] == ' ')
                continue;
            if (SignComparison(exp[i], Sign)) // функция сравнения знака на вершине и приходящего знака
            {
                while (Sign.top != 0)
                    Operands.Push(Sign.Pop());
                Sign.Push(exp[i]);
            }
            else
                Sign.Push(exp[i]);
        }

        if (exp[i] == '(')
            Sign.Push(exp[i]);

        //Если пришла буква
        if (isalpha(exp[i]))
            Operands.Push(exp[i]);

        //Если пришла ')'
        if (exp[i] == ')')
            while (Sign.top != 0)
            {
                if (Sign.elem[Sign.top - 1] != '(')
                    Operands.Push(Sign.Pop());
                else
                {
                    Sign.Pop();
                }
            }
    };

    //Дошли до конца
    while (!Sign.IsEmpty())
        Operands.Push(Sign.Pop());
    string tmp;
    tmp.assign(Operands.elem);
    cout << "\n  Postfix Form: " << Operands.elem << endl;
    return tmp;
};

int Postfix::Count(string PostForm)
{
    int count = 0;
    for (int i = 0; i < PostForm.length(); i++)
        if (isalpha(PostForm[i]))
            count++;
    return count;
}

void Postfix::Value(string& Letters, float* Numbers, string PostForm, int count)
{
    int topLetters = 0;
    float val = 0;
    char* letters = new char[count];
    float* numbers = new float[count];
    //Заполнение массива значений
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

float Postfix::CountingValue(string PostForm, string Letters, float* Numbers)
{
    Stack<float> Value(25);

    //Чтение постфиксной записи
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
            float a = Value.Pop();
            float b = Value.Pop();
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
    return Value.Pop();
};
