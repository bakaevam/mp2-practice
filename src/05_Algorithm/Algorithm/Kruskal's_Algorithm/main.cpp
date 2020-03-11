#include "Kruskal.h" 

void main()
 {
    int nodesCount = 5;
    int* m_sm = new int[nodesCount * nodesCount];

    memset(m_sm, 0, sizeof(int) * nodesCount * nodesCount);

    m_sm[1] = 1;
    m_sm[4] = 1;
    m_sm[5] = 1;
    m_sm[7] = 1;
    m_sm[9] = 1;
    m_sm[11] = 1;
    m_sm[13] = 1;
    m_sm[14] = 1;
    m_sm[17] = 1;
    m_sm[19] = 1;
    m_sm[20] = 1;
    m_sm[21] = 1;
    m_sm[22] = 1;
    m_sm[23] = 1;


    for (int i = 0; i < nodesCount; i++)
    {
        cout << endl;
        for (int j = 0; j < nodesCount; j++)
        {
            cout << " " << m_sm[i * nodesCount + j];
        }
    }

    Graph gr(m_sm, nodesCount);
    int ostavTree = Kruskal::KruskalAlg(gr);
 }