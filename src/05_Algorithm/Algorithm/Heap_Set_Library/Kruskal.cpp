#include "Kruskal.h"
#include "../Heap_Set_Library/DHeap.h"

void Kruskal::KruskalAlg(const Graph& graph, TDHeap<Edge>& result)
{
	Set nodeSet(graph.GetSize());

	//Create n singletons
	for (int i = 0; i < graph.GetSize(); i++)
	{
		nodeSet.CreateSingleton(i);
	}

	//Create queue
	TDHeap<Edge> heapEdge(graph.GetCountEdges(), 2, graph.GetEdges(), graph.GetCountEdges());
	heapEdge.Hilling();

	//Create empty set of edges, which are included in ostav tree
	Edge* edgeSet = new Edge[graph.GetCountEdges()];
	int edgeSetSize = 0;

	while ((edgeSetSize != (graph.GetSize() - 1)) && (heapEdge.GetSize() != 0))
	{
		//Take edge with min weught
		Edge e = heapEdge.GetElements()[0];

		//Find subset A, which is had begin of edge
		int subsetA = nodeSet.Find(e.GetBegin());

		//Find subset B, which is had end of edge
		int subsetB = nodeSet.Find(e.GetEnd());

		//Combine A and B subsets, put edge e in edgeSet
		if (subsetA != subsetB)
		{
			nodeSet.Combination(subsetA, subsetB);
			edgeSet[edgeSetSize++] = e;
		}

		heapEdge.DeleteMin();
	}

	TDHeap<Edge> ostavTree(edgeSetSize, 2, edgeSet, edgeSetSize);
	result = ostavTree;
};