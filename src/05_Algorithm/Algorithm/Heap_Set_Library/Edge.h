#ifndef _EDGE_H_
#define _EDGE_H_

class Edge
{
public:
	int begin;
	int end;
	int weight;

	Edge();
	Edge(const Edge&);
	Edge(int, int, int);
	~Edge();

	bool operator<(const Edge&) const;
	const Edge& operator=(const Edge&);
};

#endif