#ifndef _SET_H_
#define _SET_H_

class Set
{
private:
	int size;
	int* elements;
public:
	Set(const Set&);
	Set(int*, int);
	Set(int);
	~Set();

	void CreateSingleton(int);
	void Combination(int, int);
	int Find(int);
	int GetSize() const;
};

#endif
