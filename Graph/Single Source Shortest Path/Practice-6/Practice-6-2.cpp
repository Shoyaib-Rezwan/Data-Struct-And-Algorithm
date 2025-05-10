#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
struct Edge
{
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w)
    {
    }
};
class Graph
{
    int V;
    vector<Edge> edges;
    vector<int> distance;

public:
    Graph(int V) : V(V)
    {
        distance.resize(V-1);
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    // Graph graph(n);
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        // graph.addEdge(u, v, w);
    }
    int a, b, l, h, s, d;
    cin >> a >> b >> l >> h >> s >> d;
    // graph.bellmanFord(a, b, l, h, s, d);
}