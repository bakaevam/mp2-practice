#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include "Set.h"
#include "Edge.h"

class Graph
{
private:
	int size;
	int countEdges;
	int* nodes;
	Edge* edges;

public:
	Graph();
	Graph(const Graph&);
	Graph(int* matrix, int size);
	//Graph(int* list, int size);
	~Graph();

	int GetSize() const;
	int* GetNodes() const;
	Edge* GetEdges() const;
	int GetCountEdges() const;
	void SetCountEdges(int);
};
#endif
