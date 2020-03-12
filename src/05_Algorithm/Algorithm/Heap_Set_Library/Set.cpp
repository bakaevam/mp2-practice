#include "Set.h"

Set::Set(const Set& copy)
{
	size = copy.size;
	elements = new int[size];

	for (int i = 0; i < size; i++)
		elements[i] = copy.elements[i];
};

Set::Set(int* tmp, int n)
{
	size = n;
	elements = new int[size];

	for (int i = 0; i < size; i++)
		elements[i] = tmp[i];
};

Set::Set(int _size)
{
	size = _size;
	elements = new int[size];

	for (int i = 0; i < size; i++)
		elements[i] = -1;
};

Set::~Set()
{
	size = 0;
	delete[] elements;
};

void Set::CreateSingleton(int a)
{
	elements[a] = a;
};

void Set::Combination(int a, int b)
{
	for (int i = 0; i < size; i++)
		if (elements[i] == b)
			elements[i] = a;
};

int Set::Find(int a)
{
	return elements[a];
};

int Set::GetSize() const
{
	return size;
};