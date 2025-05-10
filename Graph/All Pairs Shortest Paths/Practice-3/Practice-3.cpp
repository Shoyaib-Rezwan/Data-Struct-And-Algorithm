#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define NEGINF INT_MIN
#define DIFF 1e-09
struct Edge
{
    int u, v;
    double w;
};
class Graph
{
    int V, flag;
    map<string, int> mp;
    vector<Edge> edges;
    vector<double> potentials;

public:
    Graph(int V)
    {
        this->V = V;
        flag = 0;
        potentials.resize(V + 1, NEGINF);
    }
    void addNode(string node)
    {
        mp.insert({node, flag});
        flag++;
    }
    void addEdge(string u, string v, double w)
    {
        edges.push_back({mp[u], mp[v], w});
    }
    void bellman_ford()
    {
        // add an extra node V
        for (int i = 0; i < V; i++)
        {
            edges.push_back({V, i, 1});
        }
        potentials[0] = 1;
        for (int i = 0; i < V; i++)
        {
            for (Edge e : edges)
            {
                if (potentials[e.u] != NEGINF && potentials[e.u] * e.w - potentials[e.v] >= DIFF)
                {
                    potentials[e.v] = potentials[e.u] * e.w;
                }
            }
        }
        for (Edge e : edges)
        {
            if (potentials[e.u] != NEGINF && potentials[e.u] * e.w - potentials[e.v] >= DIFF)
            {
                cout << "yes";
                return;
            }
        }
        cout << "no";
    }
};
int main()
{
    int n, m;
    string node;
    cin >> n;
    Graph graph(n);
    for (int i = 0; i < n; i++)
    {
        cin >> node;
        graph.addNode(node);
    }
    string u, v;
    double w;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> w >> v;
        graph.addEdge(u, v, w);
    }
    graph.bellman_ford();
}