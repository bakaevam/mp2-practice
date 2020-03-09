#ifndef _GRAPH_H_
#define _GRAPH_H_

class Graph
{
private:
	int size;
	int* AdjacencyMatrix;
	int* AdjacencyList;

public:
	Graph();
	Graph(const Graph&);
	Graph(int* matrix, int size);
	Graph(int* list, int size);
	~Graph();
};
#endif // !_GRAPH_H_
