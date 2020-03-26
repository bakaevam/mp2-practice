#include "Graph.h"
#include "Set.h"
#include "Edge.h"
#include <iostream>
#include <conio.h>
#include <queue>
#include "Exception.h"
using namespace std;

Graph::Graph()
{
	size = 0;
	countEdges = 0;
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
		nodes[i] = i;

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
					edges[k].begin = i;
					edges[k].end = j;
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

bool Graph::IsConnected() const
{
	//Создание списка смежности
	vector<vector<int>> gr(size);
	for (int i = 0; i < countEdges; i++)
	{
		gr[edges[i].begin].push_back(edges[i].end);
		gr[edges[i].end].push_back(edges[i].begin);
	};

	int visitedV = 1;
	vector<bool> visit(size);
	visit[0] = true;

	queue<int> q;
	q.push(0); // Очередь текущих вершин

	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		for (int i = 0; i < gr[v].size(); i++) //Просмотр всех ребер из текущей вершины
		{
			int curV = gr[v][i];
			if (!visit[curV])
			{
				visit[curV] = true;
				q.push(curV);
			}
		}
	}

	int _size = 0;
	for (int i = 0; i < size; i++)
		if (visit[i] == true)
			_size++;

	if (_size != size)
		return false;
	else return true;
};

istream& operator>>(istream& in, Graph& gr)
{
	cout << "Enter count of vertexes: ";
	cin >> gr.size;

	cout << " Enter count of edges: ";
	cin >> gr.countEdges;

	gr.edges = new Edge[gr.countEdges];

	for(int i = 0; i < gr.countEdges; i++)
	{
		int begin = 0;
		int end = 0;
		float weight = 0;

		do
		{
			cout << "\nEdge " << i << "\n Begin: ";
			cin >> begin;
			cout << " End: ";
			cin >> end;
			cout << " Weight = ";
			cin >> weight;

		} while ((begin < 0) || (begin >= gr.size)
			|| (end < 0) || (end >= gr.size)
			|| (weight < 0) || (begin == end));

		cout << endl;
		gr.edges[i] = Edge(begin, end, weight);
	};

	//Сonnectivity test
	if (!gr.IsConnected())
		throw Exception_errors(" Graph isn't connected!");

	return in;
};