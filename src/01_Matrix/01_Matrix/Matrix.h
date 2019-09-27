#ifndef _Matrix_H
#define _Matrix_H
#include <iostream>
#include <exception>
#include <cmath>
#include <string>
#include <cstring>
using namespace std;

template <class ValType>
class TVector
{
protected:
    int size;
    ValType *elem;
    int StartIndex;
public:
    TVector(int s = 10, int SI = 0);
    TVector(const TVector&);
    virtual ~TVector();

    int GetSize() const;
    int GetStartIndex() const;
    bool operator==(const TVector&) const;
    bool operator!=(const TVector&) const;

    TVector operator+(ValType);
    TVector operator-(ValType);
    TVector operator*(ValType);

    TVector operator+(const TVector&);
    TVector operator-(const TVector&);
    ValType operator*(const TVector&);
	double Scalar(TVector&) const;
    double Length() const;
    const TVector& operator=(const TVector&);
    ValType& operator[](int);
    const ValType& operator[](int) const;

    friend ostream& operator<<(ostream& os, const TVector& tmp)
    {
        string a = "  ";
        cout << "\n";
        os << "  | ";
        for (int i = 0; i < tmp.StartIndex; i++)
            cout << a;
        for (int i = 0; i < tmp.size; i++)
            os << tmp.elem[i] << " ";
        os << "|";
        return os;
    };
    friend istream& operator >> (istream& is, TVector& tmp)
    {
        for (int i = 0; i < tmp.size; i++)
            is >> tmp.elem[i];
        return is;
    };
};

template<class ValType>
TVector<ValType>::TVector(int s, int SI)
{
    elem = new ValType[s];
    size = s;
    StartIndex = SI;
    for (int i = 0; i < size; i++)
        elem[i] = 0;
};

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& tmp)
{
    elem = new ValType[tmp.size];
    size = tmp.size;
    StartIndex = tmp.StartIndex;
    for (int i = 0; i < size; i++)
        elem[i] = tmp.elem[i];
};

template<class ValType>
TVector<ValType>::~TVector()
{
    size = 0;
    StartIndex = 0;
    delete[] elem;
    elem = NULL;
};

template<class ValType>
int TVector<ValType>::GetSize() const
{
    return size;
};

template<class ValType>
int TVector<ValType>::GetStartIndex() const
{
    return StartIndex;
};

template<class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& tmp) const
{
    if (size != tmp.size)
        return false;
	if (StartIndex != tmp.StartIndex)
		return false;
    for (int i = 0; i < size; i++)
        if (elem[i] != tmp.elem[i])
            return false;
    return true;
};

template<class ValType>
bool TVector<ValType>::operator != (const TVector<ValType>& tmp) const
{
    return !(tmp == *this);
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator + (ValType num)
{
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] + num;
    return Vector;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator - (ValType num)
{
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] - num;
    return Vector;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(ValType num)
{
    TVector<ValType> res(size, StartIndex);
    for (int i = 0; i < size; i++)
        res.elem[i] = elem[i] * num;
    return res;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator + (const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
	if (StartIndex != tmp.StartIndex)
		throw Exception_sizes("Indexes are not equal!");
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] + tmp.elem[i];
    return Vector;
};

template<class ValType>
TVector<ValType> TVector<ValType>::operator - (const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
	if (StartIndex != tmp.StartIndex)
		throw Exception_sizes("Indexes are not equal!");
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] - tmp.elem[i];
    return Vector;
};

template<class ValType>
double TVector<ValType>::Scalar(TVector& tmp) const
{
	double res = 0;
	for (int i = 0; i < size; i++)
		res += this->[i] * this->[i]; // Scalar
	return res;
};

template<class ValType>
double TVector<ValType>::Length() const
{

    return sqrt(this->Scalar(*this));
};

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    ValType res = 0;
    for (int i = 0; i < size; i++)
        res += elem[i] * tmp.elem[i];
    return res;
};

template<class ValType>
const TVector<ValType>& TVector<ValType>::operator = (const TVector& tmp)
{
    if (this == &tmp)
        return *this;

		if (size != tmp.size)
		{
			size = tmp.size;
			delete elem;
			elem = new ValType[tmp.size];
		}
		for (int i = 0; i < size; i++)
			elem[i] = tmp.elem[i];
	return *this;

};

template<class ValType>
ValType& TVector<ValType>::operator[](int ind)
{
    if ((ind < 0) || (ind >= size))
        throw Exception_sizes("Index is not correct!");

    return elem[ind];
};

template<class ValType>
const ValType& TVector<ValType>::operator[](int ind) const
{
    if ((ind < 0) || (ind >= size))
        throw Exception_sizes("Index is not correct!");

    return elem[ind];
};


template<class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int size = 10);
    TMatrix(const TMatrix&);
    TMatrix(const TVector<TVector<ValType> > &);
    ~TMatrix();

    int GetSize() const;
    bool operator==(const TMatrix&) const;
    bool operator!=(const TMatrix&) const;

    TMatrix operator+(ValType);
    TMatrix operator-(ValType);
    TMatrix operator*(ValType);

    const TMatrix& operator=(const TMatrix&);
    TMatrix operator+(const TMatrix&);
    TMatrix operator-(const TMatrix&);
    TMatrix operator*(const TMatrix&);
    TVector<ValType> operator*(const TVector<ValType>&);

    friend ostream& operator<<(ostream& os, TMatrix& tmp)
    {
        for (int i = 0; i < tmp.size; i++)
            os << "  " << tmp.elem[i];
        return os;
    };
    friend istream& operator >> (istream& is, TMatrix& tmp)
    {
        for (int i = 0; i < tmp.size; i++)
            is >> tmp.elem[i];
        return is;
    };

};

template<class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    for (int i = 0; i < s; i++)
        elem[i] = TVector<ValType>(s - i, i);
}

template<class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& tmp) : TVector<TVector<ValType> >(tmp)
{}

template<class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > & tmp) : TVector<TVector<ValType> >(tmp)
{};

template<class ValType>
TMatrix<ValType>::~TMatrix()
{};

template<class ValType>
int TMatrix<ValType>::GetSize() const
{
    return size;
};

template<class ValType>
bool TMatrix<ValType>::operator == (const TMatrix& tmp) const
{
    if (size != tmp.size)
        return false;
	if (StartIndex != tmp.StartIndex)
		return false;
    for (int i = 0; i < size; i++)
        if (elem[i] != tmp.elem[i])
            return false;
    return true;
};

template<class ValType>
bool TMatrix<ValType>::operator != (const TMatrix<ValType>& tmp) const
{
    return !(tmp == (*this));

};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] + num;
    return Matrix;
};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] - num;
    return Matrix;
};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] * num;
    return Matrix;
};

template<class ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator = (const TMatrix& tmp)
{
    if (this != &tmp)
    {
        if (size != tmp.size)
        {
            size = tmp.size;
            delete elem;
            elem = new TVector<ValType>[tmp.size];
        }
        for (int i = 0; i < size; i++)
            elem[i] = tmp.elem[i];
    }
    return *this;
};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (const TMatrix& tmp)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] + tmp.elem[i];
    return Matrix;
};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (const TMatrix& tmp)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] - tmp.elem[i];
    return Matrix;
};

template<class ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& tmp)
{
    TVector<ValType> Vector(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < elem[i].GetSize(); j++)
            Vector[i] += elem[i][j] * tmp[i + j];

    return Vector;
};

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");

    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        for (int j = elem[i].GetStartIndex(); j < size; j++)
            for (int k = i; k <= j; k++)
                Matrix.elem[i][j - i] += elem[i][k - i] * tmp.elem[k][j - k];
    return Matrix;
};

//Exceptions
class Exception_sizes : exception
{
private:
        const string mes;
public:
        Exception_sizes(string e)
        :mes(e)
    {
    }
    const char* what() const { return mes.c_str(); }
};
#endif
