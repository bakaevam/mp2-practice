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

    int GetSize();
    bool operator==(const TVector&) const;
    bool operator!=(const TVector&) const;

    TVector operator+(ValType);
    TVector operator-(ValType);
    TVector operator*(ValType);

    TVector operator+(const TVector&);
    TVector operator-(const TVector&);
    ValType operator*(const TVector&);
    ValType Length();
    const TVector& operator=(const TVector&);
    ValType& operator[](int);

    friend ostream& operator<<(ostream& os, const TVector& tmp)
    {
        string a = "  ";
        os << "| ";
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
    memset(elem, 0, sizeof(ValType) * size);
}

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& tmp)
{
    elem = new ValType[tmp.size];
    size = tmp.size;
    StartIndex = tmp.StartIndex;
    memcpy(elem, tmp.elem, sizeof(ValType) * size);
}

template<class ValType>
TVector<ValType>::~TVector()
{
    size = 0;
    StartIndex = 0;
    delete[] elem;
    //elem = NULL;
}

template<class ValType>
int TVector<ValType>::GetSize()
{
    return size;
}

template<class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>& tmp) const
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    return (size == tmp.size);
}

template<class ValType>
bool TVector<ValType>::operator != (const TVector<ValType>& tmp) const
{
    return (size != tmp.size);
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator + (ValType num)
{
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] + num;
    return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator - (ValType num)
{
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] - num;
    return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(ValType num)
{
    TVector<ValType> res(size, StartIndex);
    for (int i = 0; i < size; i++)
        res.elem[i] = elem[i] * num;
    return res;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator + (const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] + tmp.elem[i];
    return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator - (const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    TVector<ValType> Vector(size, StartIndex);
    for (int i = 0; i < size; i++)
        Vector.elem[i] = elem[i] - tmp.elem[i];
    return Vector;
}

template<class ValType>
ValType TVector<ValType>::Length()
{
    ValType res = 0;
    for (int i = 0; i < size; i++)
        res += elem[i] * elem[i];
    return sqrt(res);
}

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& tmp)
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    ValType res = 0;
    for (int i = 0; i < size; i++)
        res = res + elem[i] * tmp.elem[i];
    return res;
}

template<class ValType>
const TVector<ValType>& TVector<ValType>::operator = (const TVector& tmp)
{
    if (this == &tmp)
        return *this;

    size = tmp.size;
    StartIndex = tmp.StartIndex;

    delete[] elem;
    elem = new ValType[size];

    for (int i = 0; i < size; i++)
        elem[i] = tmp.elem[i];

    return *this;
}

template<class ValType>
ValType& TVector<ValType>::operator[](int ind)
{
    if ((ind < 0) || (ind > size))
    {
        throw Exception_sizes("Index is not correct!");
    }
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

    int GetSize();
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
            os << "  " << tmp.elem[i] << endl;
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
    {
        elem[i] = TVector<ValType>(s - i, i);
    }
}

template<class ValType>
TMatrix<ValType>::TMatrix(const TMatrix& tmp) : TVector<TVector<ValType> >(tmp)
{}

template<class ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > & tmp) : TVector<TVector<ValType> >(tmp)
{}

template<class ValType>
TMatrix<ValType>::~TMatrix()
{}

template<class ValType>
int TMatrix<ValType>::GetSize()
{
    return size;
}

template<class ValType>
bool TMatrix<ValType>::operator == (const TMatrix& tmp) const
{
    if (size != tmp.size)
        throw Exception_sizes("Sizes are not equal!");
    return (size == tmp.size);
}

template<class ValType>
bool TMatrix<ValType>::operator != (const TMatrix<ValType>& tmp) const
{
    return (size != tmp.size);
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] + num;
    return Matrix;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] - num;
    return Matrix;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(ValType num)
{
    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] * num;
    return Matrix;
}

template<class ValType>
const TMatrix<ValType>& TMatrix<ValType>::operator = (const TMatrix& tmp)
{
    TVector<TVector<ValType> >::operator=(tmp);
    return *this;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator + (const TMatrix& tmp)
{
    TMatrix<ValType> Matrix(size, StartIndex);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] + tmp.elem[i];
    return Matrix;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator - (const TMatrix& tmp)
{
    TMatrix<ValType> Matrix(size, StartIndex);
    for (int i = 0; i < size; i++)
        Matrix.elem[i] = elem[i] - tmp.elem[i];
    return Matrix;
}

template<class ValType>
TVector<ValType> TMatrix<ValType>::operator*(const TVector<ValType>& tmp)
{
    if (size != tmp.GetSize)
        throw Exception_sizes("Sizes are not equal!");
    TVector<ValType> Vector(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            Vector[i] +=
            (elem[i * size + j] * tmp[j]);
    return Vector;
}

template<class ValType>
TMatrix<ValType> TMatrix<ValType>::operator*(const TMatrix& tmp)
{
    if (size != tmp.size)
    {
        throw Exception_sizes("Sizes are not equal!");
    }

    TMatrix<ValType> Matrix(size);
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; i++)
            Matrix.elem[i * size + j] = Matrix.elem[i * size + j] +
            (elem[i * size + j] * tmp.elem[i * size + j]);
    return Matrix;
}

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
