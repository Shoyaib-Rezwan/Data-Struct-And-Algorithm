#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define vvi vector<vector<int>>
class Graph
{
    int V;
    vvi W;
    void extendedShortestPath(const vvi &L, vvi &M)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                for (int k = 0; k < V; k++)
                {
                    if (L[i][k] == INF || W[k][j] == INF)
                        continue;
                    M[i][j] = min(M[i][j], L[i][k] + W[k][j]);
                }
            }
        }
    }

public:
    Graph(int V)
    {
        this->V = V;
        W.resize(V, vector<int>(V, INF));
        for (int i = 0; i < V; i++)
        {
            W[i][i] = 0;
        }
    }
    void addEdge(int u, int v, int w)
    {
        W[u][v] = w;
    }
    void slowAPSP()
    {
        vvi L = W;

        for (int i = 1; i < V - 1; i++)
        {
            vvi M(V, vector<int>(V, INF));
            extendedShortestPath(L, M);
            L = M;
        }
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << L[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    void fastAPSP()
    {
        vvi L = W;
        int r = 1;
        while (r < V - 1)
        {
            extendedShortestPath(L, L);
            W = L;
            r = 2 * r;
        }
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (L[i][j] == INF)
                {
                    cout << "INF ";
                    continue;
                }
                cout << L[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};
int main()
{
    int V, E;
    cin >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u - 1, v - 1, w);
    }
    graph.fastAPSP();
}