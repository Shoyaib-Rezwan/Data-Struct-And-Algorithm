#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pid pair<int, double>
#define pdi pair<double, int>
#define INF INT32_MAX
#define NEGINF -1.0
class Graph
{
    int V;
    vector<vector<pid>> adj;
    vector<double> reliability;
    vector<int> parent;

    void getPath(int u, vector<int> &path)
    {
        if (parent[u] != -1)
            getPath(parent[u], path);
        path.push_back(u);
    }

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
        reliability.resize(V, NEGINF);
        parent.resize(V, -1);
    }
    void addEdge(int u, int v, double r)
    {
        adj[u].push_back({v, r});
    }
    void dijkstra(int src, int dst)
    {
        reliability[src] = 1;
        priority_queue<pdi> pq;
        pq.push({1.0, src});
        while (!pq.empty())
        {
            int u = pq.top().second;
            double r = pq.top().first;
            pq.pop();
            if (reliability[u] > r)
            {
                continue;
            }
            for (pid x : adj[u])
            {
                if (reliability[x.first] < reliability[u] * x.second)
                {
                    reliability[x.first] = reliability[u] * x.second;
                    parent[x.first] = u;
                    pq.push({reliability[x.first], x.first});
                }
            }
        }
        cout << reliability[dst] << '\n';
        vector<int> path;
        getPath(dst, path);
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i] << " -> ";
        }
        cout<< path[path.size() - 1];
    }
};
int main()
{
    int V, E, u, v;
    double r;
    cin >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> r;
        graph.addEdge(u, v, r);
    }
    int src, dst;
    cin >> src >> dst;
    graph.dijkstra(src, dst);
}