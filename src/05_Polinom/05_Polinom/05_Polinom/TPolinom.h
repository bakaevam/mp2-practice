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
    TPolinom(const string&);
    TPolinom(TList<int, float>*);
    TPolinom(const TPolinom&);
    ~TPolinom();

    void Simplification();
    void StandartView();
	bool operator==(const TPolinom&) const;
    const TPolinom& operator=(const TPolinom&);
    TPolinom operator+(const TPolinom&);
    TPolinom operator-(const TPolinom&);
    TPolinom operator*(const TPolinom&);
    TPolinom operator-();
    
    friend ostream& operator<<(ostream& os, TPolinom& tmp);
};


TPolinom::TPolinom()
{
    monoms = new TList<int, float>();
};

TPolinom::TPolinom(const string& Userstr)
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
                if (s[i + 1] == '.')
                {
                    c += s[i];
                    c += s[i + 1];
                    i = i + 2;
                }
                else 
                {
                    c += s[i];
                    i++;
                }
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
        if (tmp->GetpCurr()->Key > 999) // <0 // int -> unsigned int
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
	monoms->Reset();

	while (!monoms->IsEnded())
	{
		TNode<int, float>* tmp = monoms->GetpFirst();
		while ((tmp->Key != monoms->GetpCurr()->Key))
			tmp = tmp->pNext;
		if (tmp == monoms->GetpCurr())
		{
			monoms->Next();
			continue;
		};
		monoms->GetpCurr()->data += tmp->data;
		monoms->Remove(tmp->Key);
		monoms->Next();
	};
};

void TPolinom::StandartView()
{
	if (monoms->GetpFirst() == nullptr)
		return;

	if (monoms->GetpFirst()->pNext == nullptr)
		return;

	monoms->Reset();

	TNode<int, float>* t, *m, *a, *b;
	for (bool isDone = true; isDone;)
	{
		isDone = false;
		a = t = monoms->GetpFirst();
		b = monoms->GetpFirst()->pNext;

		while (b != nullptr)
		{
			if (a->Key > b->Key)
			{
				if (t == a)
					monoms->pFirst = b;
				else t->pNext = b;

				a->pNext = b->pNext;
				b->pNext = a;

				m = a;
				a = b;
				b = m;
				isDone = true;
			}
			t = a;
			a = a->pNext;
			b = b->pNext;
		}
	}
};

const TPolinom& TPolinom::operator=(const TPolinom& tmp)
{
    if (*this == tmp)
        return *this;

    if (monoms->GetpFirst())
        delete monoms;

    monoms = new TList<int, float>(*tmp.monoms);
    return *this;
};

TPolinom TPolinom::operator+(const TPolinom& tmp)
{
    tmp.monoms->Reset();
    TPolinom res(*this);


    while (!tmp.monoms->IsEnded())
    {
        res.monoms->Reset();
        while (!(res.monoms->IsEnded()) && (tmp.monoms->GetpCurr() <= res.monoms->GetpCurr()))
            res.monoms->Next();

        if (res.monoms->GetpCurr() == nullptr)
        {
            res.monoms->InsertToEnd(tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
		}
		else
        {
          /*  TNode<int, float>* curr = res.monoms->pCurr;
            while (!res.monoms->IsEnded() && (res.monoms->pCurr->Key != tmp.monoms->GetpCurr()->Key))
                tmp.monoms->Next();

            if(res.monoms->pCurr != nullptr)
                res.monoms->pCurr->data += tmp.monoms->GetpCurr()->data;
            else
            {
                res.monoms->pCurr = curr;*/
                res.monoms->InsertBefore(res.monoms->GetpCurr()->Key,
                    tmp.monoms->GetpCurr()->Key, tmp.monoms->GetpCurr()->data);
            //}
        }
        tmp.monoms->Next();
		//cout << res.monoms->pCurr->Key;
    };
   // res.StandartView();
    return res;
};

TPolinom TPolinom::operator-(const TPolinom& tmp)
{
    TPolinom res(tmp);
    return (*this + (-res));
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
            TNode<int, float>* _res;
            _res = *tmp.monoms->GetpCurr() * *monoms->GetpCurr();
            res.monoms->InsertToEnd(_res->Key, _res->data);
            tmp.monoms->Next();
        }
        monoms->Next();
    }

    res.Simplification();
    res.StandartView();
    return res;
};

TPolinom TPolinom::operator-()
{
    TPolinom tmp(*this);

    while (!tmp.monoms->IsEnded())
    {
        tmp.monoms->pCurr->data *= (-1);
        tmp.monoms->Next();
    };

    tmp.monoms->Reset();
    return tmp;
};

bool TPolinom::operator==(const TPolinom& tmp) const
{
    return(*(this->monoms) == *(tmp.monoms));
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