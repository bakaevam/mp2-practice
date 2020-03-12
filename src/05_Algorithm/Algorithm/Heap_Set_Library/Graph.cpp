#include "Graph.h"
#include "Set.h"
#include "Edge.h"
#include <iostream>
using namespace std;

Graph::Graph()
{
	size = 0;
	countEdges = 0;
	nodes = new int[size];
	edges = new Edge();
};

Graph::Graph(const Graph& copy)
{
	size = copy.size;
	countEdges = copy.countEdges;
	nodes = new int(*copy.nodes);
	edges = new Edge[countEdges];
	
	for (int i = 0; i < countEdges; i++)
	{
		edges[i].begin = copy.edges[i].begin;
		edges[i].end = copy.edges[i].end;
		edges[i].weight = copy.edges[i].weight;
	}
};

Graph::Graph(int* matrix, int _size)
{
	size = _size;
	nodes = new int[size];

	for (int i = 0; i < size; i++)
		nodes[i] = i + 1;

	for(int i = 0; i < size; i++)
		for (int j = 0; j < i; j++)
		{
			if (matrix[i * size + j] == 1)
				countEdges++;
		}

	edges = new Edge[countEdges];
	int k = 0;

	while (k != countEdges)
	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < i; j++)
			{
				if (matrix[i * size + j] == 1)
				{
					edges[k].begin = i + 1;
					edges[k].end = j + 1;
					k++;
				}

			}
	}

	for (int i = 0; i < countEdges; i++)
	{
		cout << endl << " Weight of edge " << edges[i].begin << " - " << edges[i].end << " : ";
		cin >> edges[i].weight;
	}
};

Graph::~Graph()
{
	size = 0;
	countEdges = 0;
	delete[] nodes;
	delete[] edges;
};

int Graph::GetSize() const
{
	return size;
};

int* Graph::GetNodes() const
{
	return nodes;
};

Edge* Graph::GetEdges() const
{
	return edges;
};

int Graph::GetCountEdges() const
{
	return countEdges;
};

void Graph::SetCountEdges(int a)
{
	countEdges = a;
};