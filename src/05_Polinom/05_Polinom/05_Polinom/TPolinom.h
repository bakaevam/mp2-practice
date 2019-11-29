#ifndef _TPOLINOM_H_
#define _TPOLINOM_H_
#include "TList_Polinom.h"
#include "TNode_Polinom.h"
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

class TPolinom
{
private:
    TList<int, float>* monoms;
public:
    TPolinom();
    TPolinom(const string);
    TPolinom(TList<int, float>*);
    TPolinom(const TPolinom&);
    ~TPolinom();

    void Simplification();
    void StandartView();
    const TPolinom& operator=(const TPolinom&);
    TPolinom operator+(const TPolinom&);
    TPolinom operator-(const TPolinom&);
    TPolinom operator*(const TPolinom&);
    
    friend ostream& operator<<(ostream& os, TPolinom& tmp);
    friend istream& operator >> (istream& is, const TPolinom& tmp);
};


TPolinom::TPolinom()
{
    monoms = new TList<int, float>();
};

TPolinom::TPolinom(const string Userstr)
{
    monoms = new TList<int, float>();

    string s = Userstr;
    float coeff = 1;
    int deg = 0;
    int i = 0;
    bool xf = false;
    bool yf = false;
    bool zf = false;

    while(i < s.length())
    {
        do
        {

            if (s[i] == '^')
            {
                i++;
                continue;
            };

        if (isdigit(s[i]) && !xf && !yf && !zf)
        {
            coeff *= s[i] - 48;
            i++;
            continue;
        };

        if (s[i] == 'x')
        {
            i++;
            xf = true;
            yf = false;
            zf = false;

            continue;
        };

        if ((xf == true) && ((s[i] == 'y') || (s[i] == 'z')))
        {
            xf = false;
            deg += 100;
        };

        if (s[i] == 'y')
        {
            i++;
            xf = false;
            yf = true;
            zf = false;

            continue;
        };

        if ((yf == true) && ((s[i] == 'x') || (s[i] == 'z')))
        {
            yf = false;
            deg += 10;
        };

        if (s[i] == 'z')
        {
            i++;
            xf = false;
            yf = false;
            zf = true;

            continue;
        };

        if ((zf == true) && !(isdigit(s[i])))
        {
            zf = false;
            deg += 1;
        };

        if (s[i] == '+')
        {
            i++;
            continue;
        };

        if (s[i] == '-')
        {
            i++;
            coeff *= (-1);
            continue;
        };

        if ((xf == true) && (isdigit(s[i])))
        {
            if ((s[i] - 48) > 9)
                throw Exception_errors("  Degree should be no more then 9");

            deg += ((int)s[i] - 48) * 100;
            xf = false;
            i++;
            continue;
        };

        if ((yf == true) && (isdigit(s[i])))
        {
            if ((s[i] - 48) > 9)
                throw Exception_errors("  Degree should be no more then 9");

            deg += ((int)s[i] - 48) * 10;
            yf = false;
            i++;

            continue;
        };

        if ((zf == true) && (isdigit(s[i])))
        {
            if ((s[i] - 48) > 9)
                throw Exception_errors("  Degree should be no more then 9");

            deg += ((int)s[i] - 48);
            zf = false;
            i++;

            continue;
        };

		if (s[i] == ' ')
		{
			i++;
			continue;
		};

    }while (!((s[i] == '+') || (s[i] == '-')) && (i != s.length()));

                monoms->InsertToEnd(deg, coeff);
                coeff = 1;
                deg = 0;
    };
};

TPolinom::TPolinom(TList<int, float>* tmp)
{
    while (!tmp->IsEnded())
    {
        if (tmp->GetpCurr()->Key > 999)
        {
            throw Exception_errors("  Degree shouldn't exceed 9");
            return;
        };
        tmp->Next();
    };

    monoms = new TList<int, float>(*tmp);
};

TPolinom::TPolinom(const TPolinom& tmp)
{
    monoms = new TList<int, float>(*tmp.monoms);
};

TPolinom::~TPolinom()
{
    delete monoms;
};

void TPolinom::Simplification()
{
    monoms->Simple();
};

void TPolinom::StandartView()
{
    monoms->MergeSort((monoms->GetpFirst()));
};

const TPolinom& TPolinom::operator=(const TPolinom& tmp)
{
    if (this == &tmp)
        return *this;

    if (monoms->GetpFirst())
        delete monoms;

    monoms = new TList<int, float>(*tmp.monoms);
    return *this;
};

TPolinom TPolinom::operator+(const TPolinom& tmp)
{
    tmp.monoms->Reset();
    TNode<int, float>* i = tmp.monoms->GetpCurr();
    TPolinom res(*this);

    tmp.monoms->Reset();
    while (!tmp.monoms->IsEnded())
    {
        res.monoms->Reset();
        while ((!res.monoms->IsEnded()) && (tmp.monoms->GetpCurr()->Key != res.monoms->GetpCurr()->Key))
            res.monoms->Next();

        if (res.monoms->IsEnded())
        {
            res.monoms->InsertToEnd(tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
            tmp.monoms->Next();
            continue;
        };

        res.monoms->GetpCurr()->data += tmp.monoms->GetpCurr()->data;
        tmp.monoms->Next();
    };

    return res;
};

TPolinom TPolinom::operator-(const TPolinom& tmp)
{
    tmp.monoms->Reset();
    TNode<int, float>* i = tmp.monoms->GetpCurr();
    TPolinom res(*this);

    tmp.monoms->Reset();
    while (!tmp.monoms->IsEnded())
    {
        res.monoms->Reset();
        while ((!res.monoms->IsEnded()) && (tmp.monoms->GetpCurr()->Key != res.monoms->GetpCurr()->Key))
            res.monoms->Next();

        if (res.monoms->IsEnded())
        {
            res.monoms->InsertToEnd(tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
            tmp.monoms->Next();
            continue;
        };

        res.monoms->GetpCurr()->data -= tmp.monoms->GetpCurr()->data;
        tmp.monoms->Next();
    };

    return res;
};

ostream& operator<<(ostream& os,TPolinom& tmp)
{
    tmp.monoms->Reset();
    os << "  ";
    while (tmp.monoms->GetpCurr() != nullptr)
    {
        int degX = 0;
        int degY = 0;
        int degZ = 0;
        int deg = tmp.monoms->GetpCurr()->Key;

        degX = deg / 100;
        degY = (deg % 100) / 10;
        degZ = deg % 10;

        if (tmp.monoms->GetpCurr() == tmp.monoms->GetpFirst())
        {
            if (tmp.monoms->GetpCurr()->data != 1)
                os << tmp.monoms->GetpCurr()->data << "*";
        }
        else
        {
            if (tmp.monoms->GetpCurr()->data != 1)
            {
                if (tmp.monoms->GetpCurr()->data < 0)
                    if (deg == 0)
                        os << tmp.monoms->GetpCurr()->data;
                    else
                    os << tmp.monoms->GetpCurr()->data << "*";

                if (tmp.monoms->GetpCurr()->data > 0)
                    if (deg == 0)
                        os << " + " << tmp.monoms->GetpCurr()->data;
                    else
                    os << " + " << tmp.monoms->GetpCurr()->data << "*";
            }

            if (tmp.monoms->GetpCurr()->data == 1)
                os << " + ";
            if ((tmp.monoms->GetpCurr()->data == 1) && (deg = 0))
                os << " + " << tmp.monoms->GetpCurr()->data;
            if ((tmp.monoms->GetpCurr()->data == -1) && (deg = 0))
                os << tmp.monoms->GetpCurr()->data;
        };

            if ((degX != 1) && (degX != 0))
                os << "x^" << degX << "*";
            if (degX == 1)
                os << "x" << "*";

            if ((degY != 1) && (degY != 0))
                os << "y^" << degY << "*";
            if (degY == 1)
                os << "y" << "*";

            if ((degZ != 1) && (degZ != 0))
                os << "z^" << degZ;
            if (degZ == 1)
                os << "z";

            //if(tmp.monoms->GetpCurr()->pNext != nullptr)
              //  cout << " + ";
        tmp.monoms->Next();
    };
    os << endl;
    return os;
};

#endif