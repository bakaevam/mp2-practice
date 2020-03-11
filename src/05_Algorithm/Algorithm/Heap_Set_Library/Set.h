#ifndef _SET_H_
#define _SET_H_


class Set
{
private:
	int size;
	int currentSize;
	int* elements;
public:
	Set();
	Set(const Set&);
	Set(int*, int);
	~Set();

	void CreateSingleton(int);
	void Combination(int, int);
	int Find(int);
	int GetSize() const;
};

#endif
