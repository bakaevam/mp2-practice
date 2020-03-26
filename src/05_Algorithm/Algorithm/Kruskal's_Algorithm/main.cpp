#include "../Heap_Set_Library/Kruskal.h" 
#include "../Heap_Set_Library/Exception.h"

void main()
 {
    Graph gr;
    try 
    {
        cin >> gr;
    }
    catch (Exception_errors & e)
    {
        cerr << e.what() << endl;
    }

    TDHeap<Edge> ostavTree;
    Kruskal::KruskalAlg(gr, ostavTree);

    for (int i = 0; i < ostavTree.GetSize(); i++)
    {
        cout << endl << ostavTree.GetElements()[i].GetBegin();
        cout << " - " << ostavTree.GetElements()[i].GetEnd();
        cout << " w = " << ostavTree.GetElements()[i].GetWeight();
    }
 }