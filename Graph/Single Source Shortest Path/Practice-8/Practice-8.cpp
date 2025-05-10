#include <bits/stdc++.h>
using namespace std;
#define NEGINF INT_MIN
#define DIFF 1e-09
struct Edge
{
    int u, v;
    double w;
};
class Graph
{
    int V;
    vector<Edge> edges;
    vector<double> rates;
    vector<int> parent;

    void getPath(int u, vector<int> &path)
    {
        if (parent[u] == -1)
        {
            path.push_back(u);
        }
        else
        {
            getPath(parent[u], path);
            path.push_back(u);
        }
    }

public:
    Graph(int V)
    {
        this->V = V;
        rates.resize(V, NEGINF);
        parent.resize(V, -1);
    }
    void addEdge(int u, int v, double w)
    {
        edges.push_back({u, v, w});
    }
    void bellman_ford(int s, int d)
    {

        rates[s] = 1;
        for (int i = 0; i < V - 1; i++)
        {
            for (Edge x : edges)
            {

                if (rates[x.u] != NEGINF && rates[x.u] * x.w - rates[x.v] >= DIFF)
                {
                    rates[x.v] = rates[x.u] * x.w;
                    parent[x.v] = x.u;
                }
            }
        }

        for (Edge x : edges)
        {
            if (rates[x.u] != NEGINF && rates[x.u] * x.w - rates[x.v] >= DIFF)
            {
                cout << "There is an anomaly!";
                return;
            }
        }
        cout << "Best exchange rate: " << rates[d] << '\n';
        vector<int> path;
        getPath(d, path);
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i] << "->";
        }
        cout << d;
    }
};
int main()
{
    int n, m, u, v;
    double w;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    int s, d;
    cin >> s >> d;
    graph.bellman_ford(s, d);
}