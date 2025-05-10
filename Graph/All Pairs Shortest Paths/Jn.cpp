#include <bits/stdc++.h>
using namespace std;
#define INF INT32_MAX
#define pii pair<int, int>
struct Edge
{
    int u, v, w;
};
class Graph
{
    vector<Edge> edges;
    vector<vector<pii>> adj;
    vector<vector<int>> predecessor, distance;
    vector<int> potentials;
    int n;

    void bellman_ford()
    {
    }

public:
    Graph(int V)
    {
        n = V;
        adj.resize(V);
        predecessor.resize(n, vector<int>(n, -1));
        distance.resize(n, vector<int>(n, INF));
        for (int i = 0; i < V; i++)
        {
            distance[i][i] = 0;
        }
        potentials.resize(V + 1, INF);
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({u, v, w});
        adj[u].push_back({v, w});
        predecessor[u][v] = u;
    }
    void getPath(int u, int v, vector<int> &path)
    {
    }
};
int main()
{
    int V, E, u, v, w;
    cin >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u - 1, v - 1, w);
    }
    // graph.floyd_warshall();
}