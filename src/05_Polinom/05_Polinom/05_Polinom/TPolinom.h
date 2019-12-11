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
            string c;
            while (isdigit(s[i]))
            {
                c += s[i];
                i++;
            }
            coeff *= (float)(atof(c.c_str()));
            continue;
        };

        if (s[i] == 'x')
        {
            if ((i + 1) != s.length())
            {
                i++;
                xf = true;
                yf = false;
                zf = false;

                continue;
            }
            xf = true;
            yf = false;
            zf = false;
        };

        if ((xf == true) && ((s[i] == 'y') || (s[i] == 'z') || (s[i] == ' ')))
        {
            xf = false;
            deg += 100;
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

        if (((i + 1) == s.length()) && (xf == true))
        {
            xf = false;
            deg += 100;
            i++;
        };

        if (s[i] == 'y')
        {
            if ((i + 1) != s.length())
            {
                i++;
                xf = false;
                yf = true;
                zf = false;

                continue;
            }
            xf = false;
            yf = true;
            zf = false;
        };

        if ((yf == true) && ((s[i] == 'x') || (s[i] == 'z') || (s[i] == ' ')))
        {
            yf = false;
            deg += 10;
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

        if (((i + 1) == s.length()) && (yf == true))
        {
            yf = false;
            deg += 10;
            i++;
        };

        if (s[i] == 'z')
        {
            if ((i + 1) != s.length())
            {
                i++;
                xf = false;
                yf = false;
                zf = true;

                continue;
            }
            xf = false;
            yf = false;
            zf = true;
        };

        if (((i + 1) == s.length()) && (zf == true))
        {
            zf = false;
            deg += 1;
            i++;
            continue;
        };

        if ((zf == true) && !(isdigit(s[i])))
        {
            zf = false;
            deg += 1;
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

        if((s[i] == ' ') && (zf == true))
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

		if (s[i] == ' ')
		{
			i++;
			continue;
		};

    }while (!((s[i] == '+') || (s[i] == '-')) && (i != s.length()) && (!xf || !yf || !zf));

                monoms->InsertToEnd(deg, coeff);
                coeff = 1;
                deg = 0;
    };

    StandartView();
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
    StandartView();
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
    monoms->Sort();
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

    while (!tmp.monoms->IsEnded())
    {
        res.monoms->Reset();
        while (!(res.monoms->IsEnded()) && (tmp.monoms->GetpCurr()->Key >= res.monoms->GetpCurr()->Key))
            res.monoms->Next();

        if (res.monoms->GetpCurr() != nullptr)
        {
            res.monoms->InsertToEnd(tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
            tmp.monoms->Next();
            continue;
        };
        if (res.monoms->GetpCurr() == nullptr)
        {
            res.monoms->InsertBefore(res.monoms->GetpPrev()->Key,
                tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
            tmp.monoms->Next();
            continue;
        }

        res.monoms->InsertBefore(res.monoms->GetpCurr()->Key,
            tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
        tmp.monoms->Next();
    };
    res.Simplification();
    return res;
};

TPolinom TPolinom::operator-(const TPolinom& tmp)
{
    tmp.monoms->Reset();
    TNode<int, float>* i = tmp.monoms->GetpCurr();
    TPolinom res(*this);

    while (!tmp.monoms->IsEnded())
    {
        res.monoms->Reset();
        while (!(res.monoms->IsEnded()) && (tmp.monoms->GetpCurr()->Key >= res.monoms->GetpCurr()->Key))
            res.monoms->Next();

        float node = tmp.monoms->GetpCurr()->data * (-1);

        if (res.monoms->GetpCurr() != nullptr)
        {
            res.monoms->InsertToEnd(tmp.monoms->GetpCurr()->Key, node);
            tmp.monoms->Next();
            continue;
        };
        if (res.monoms->GetpCurr() == nullptr)
        {
            res.monoms->InsertBefore(res.monoms->GetpPrev()->Key,
                tmp.monoms->GetpCurr()->Key, node);
            tmp.monoms->Next();
            continue;
        }

        res.monoms->InsertBefore(res.monoms->GetpCurr()->Key,
            tmp.monoms->GetpCurr()->Key, node);
        tmp.monoms->Next();
    };
    res.Simplification();
    res.StandartView();

    return res;
};

TPolinom TPolinom::operator*(const TPolinom& tmp)
{
    TPolinom res;

    monoms->Reset();
    while (!monoms->IsEnded())
    {
        tmp.monoms->Reset();
        while (!tmp.monoms->IsEnded())
        {
            float newCoeff = tmp.monoms->GetpCurr()->data * monoms->GetpCurr()->data;
            int degX = 0;
            int degY = 0;
            int degZ = 0;
            int deg = tmp.monoms->GetpCurr()->Key;

            degX = deg / 100;
            degY = (deg % 100) / 10;
            degZ = deg % 10;

            int _degX = 0;
            int _degY = 0;
            int _degZ = 0;
            int _deg = monoms->GetpCurr()->Key;

            _degX = _deg / 100;
            _degY = (_deg % 100) / 10;
            _degZ = _deg % 10;

            if ((degX + _degX > 9) || ((degY + _degY > 9) || (degZ + _degZ > 9)))
            {
                throw Exception_errors("  Degree shouldn't exceed 9");
            };

            int newDeg = (degX + _degX) * 100 + (degY + _degY) * 10 + (degZ + _degZ);
            res.monoms->InsertToEnd(newDeg, newCoeff);
            tmp.monoms->Next();
        }
        monoms->Next();
    }

    res.Simplification();
    res.StandartView();
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

        if (tmp.monoms->GetpCurr()->data == 0)
        {
            tmp.monoms->Next();
            continue;
        }

        if (tmp.monoms->GetpCurr() == tmp.monoms->GetpFirst())
        {
            if (tmp.monoms->GetpCurr()->data != 1)
                if (tmp.monoms->GetpCurr()->Key == 0)
                    os << tmp.monoms->GetpCurr()->data;
                else
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

        if (tmp.monoms->GetpCurr()->pNext != nullptr)
        {
            if ((degX != 1) && (degY == 0) && (degX != 0))
                os << "x^" << degX;
            if ((degX != 1) && (degX != 0) && ((degY != 0) || (degZ != 0)))
                os << "x^" << degX << "*";
            if ((degX == 1) && (degY == 0) && (degZ == 0))
                os << "x";
            if ((degX == 1) && ((degY != 0) || (degZ != 0)))
                os << "x" << "*";


            if ((degY != 1) && (degY != 0) && (degZ != 0))
                os << "y^" << degY << "*";
            if ((degY != 1) && (degZ == 0) && (degY != 0))
                os << "y^" << degY;
            if ((degY == 1) && (degZ == 0))
                os << "y";
            if ((degY == 1) && (degZ != 0))
                os << "y" << "*";

            if ((degZ != 1) && (degZ != 0))
                os << "z^" << degZ;
            if (degZ == 1)
                os << "z";
        }
        else
        {
            if ((degX != 1) && (degX != 0))
                os << "x^" << degX;
            if (degX == 1)
                os << "x";

            if ((degY != 1) && (degY != 0))
                os << "y^" << degY;
            if (degY == 1)
                os << "y";

            if ((degZ != 1) && (degZ != 0))
                os << "z^" << degZ;
            if (degZ == 1)
                os << "z";
        }

        tmp.monoms->Next();
    };
    os << endl;
    return os;
};

#endif