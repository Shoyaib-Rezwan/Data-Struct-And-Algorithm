#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
struct Edge
{
    int u, v, w;
};
class Graph
{
    int V;
    vector<Edge> edges;
    vector<int> potentials;

public:
    Graph(int V)
    {
        this->V = V;
        potentials.resize(V + 1, INF);
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({u, v, w});
    }
    void bellman_ford()
    {
        for (int i = 0; i < V; i++)
        {
            edges.push_back({V, i, 0});
        }
        potentials[V] = 0;
        for (int i = 0; i < V; i++)
        {
            for (Edge e : edges)
            {
                if (potentials[e.u] != INF && potentials[e.v] > potentials[e.u] + e.w)
                {
                    potentials[e.v] = potentials[e.u] + e.w;
                }
            }
        }
        for (Edge e : edges)
        {
            if (potentials[e.u] != INF && potentials[e.v] > potentials[e.u] + e.w)
            {
                cout << "YES";
                return;
            }
        }
        cout << "NO";
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    graph.bellman_ford();
}