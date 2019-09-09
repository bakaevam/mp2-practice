#ifndef _Matrix_H
#define _Matrix_H
#include <iostream>
using namespace std;

template <class ValType>
class TVector
{protected:
	int size;
	ValType* elem;
	int StartIndex;
public: 
	TVector(int size = 10; int StartIndex = 0);
	TVector(const TVector&);
	~TVector();

	bool operator==(const TVector&) const;
	bool operator!=(const TVector&) const;

	TVector operator+(ValType);
	TVector operator-(ValType);
	TVector operator*(ValType);

	TVector operator+(const TVector&);
	TVector operator-(const TVector&);
	ValType operator*(const TVector&);
	const TVector& operator=(const TVector&);
	ValType& operator[](int ind)

	friend ostream operator<<(ostream&, const TVector&);
	friend istream operator>>(istream&, TVector&);
};

template<class ValType>
TVector<ValType>::TVector(const TVector<ValType>& tmp)
{
	tmp.size = size;
	tmp.StartIndex = StartIndex;
	Vector = new ValType[size];
	memcpy(tmp, Vector, sizeof(ValType) * size);
}

template<class ValType>
TVector<ValType>::~TVector()
{
	size = 0;
	StartIndex = 0;
	delete[]elem;
}

template<class ValType>
bool TVector<ValType>::operator==(const TVector<ValType>&) const
{
	//Exp if sizes don't equel
}

template<class ValType>
bool TVector<ValType>::operator!=(const TVector<ValType>&) const
{
	//Exp if sizes don't equel
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(ValType num)
{
	TVector<ValType> Vector(size, StartIndex);
	for (int i = 0; i < size; i++)
		Vector.elem[i] = elem[i] + num;
	return Vector;

}

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(ValType num)
{
	TVector<ValType> Vector(size, StartIndex);
	for (int i = 0; i < size; i++)
		Vector.elem[i] = elem[i] - num;
	return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator*(ValType num)
{
	TVector<ValType> Vector(size, StartIndex);
	for (int i = 0; i < size; i++)
		Vector.elem[i] = elem[i] * num;
	return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator+(const TVector& tmp)
{
	TVector Vector(size, StartIndex);
	for (int i = 0; i < size; i++)
		Vector.elem[i] = elem[i] + tmp.elem[i];
	return Vector;
}

template<class ValType>
TVector<ValType> TVector<ValType>::operator-(const TVector& tmp)
{
	TVector Vector(size, StartIndex);
	for (int i = 0; i < size; i++)
		Vector.elem[i] = elem[i] - tmp.elem[i];
	return Vector;
}

template<class ValType>
ValType TVector<ValType>::operator*(const TVector& tmp)
{
	ValType res = 0;
	for (int i = 0; i < size; i++)
		res = res + elem[i] * tmp.elem[i];
	return res;
}
#endif
