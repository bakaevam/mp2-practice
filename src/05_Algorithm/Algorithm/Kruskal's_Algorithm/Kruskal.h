#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_
#include "../Heap_Set_Library/Graph.h"
#include "../Heap_Set_Library/DHeap.h"
#include "../Heap_Set_Library/Edge.h"

class Kruskal
{
public:
	static TDHeap<Edge> KruskalAlg(const Graph&);
};

#endif 

