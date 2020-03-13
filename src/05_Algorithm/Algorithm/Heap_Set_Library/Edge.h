#ifndef _EDGE_H_
#define _EDGE_H_

class Edge
{
private:
	int begin;
	int end;
	float weight;

public:
	Edge();
	Edge(const Edge&);
	Edge(int, int, float);
	~Edge();

	bool operator<(const Edge&) const;
	const Edge& operator=(const Edge&);
	int GetBegin() const;
	int GetEnd() const;
	float GetWeight() const;

	friend class Graph;
};

#endif