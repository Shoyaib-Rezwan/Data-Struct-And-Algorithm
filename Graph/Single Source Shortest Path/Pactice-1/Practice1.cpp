#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define pii pair<int, int>
class Graph
{
    int V;
    vector<int> taxes;
    vector<int> cost;
    vector<vector<int>> adj;

public:
    Graph(int V)
    {
        this->V = V;
        cost.resize(V, INF);
        cost[0] = 0;
        adj.resize(V);
    }
    void addTax(int tax)
    {
        taxes.push_back(tax);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }
    void dijkstra()
    {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, 0});
        int u, cost_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            cost_u = pq.top().first;
            pq.pop();
            if (cost[u] < cost_u)
                continue;
            for (int v : adj[u])
            {
                if (cost[v] > cost[u] + taxes[v])
                {
                    cost[v] = cost[u] + taxes[v];
                    pq.push({cost[v], v});
                }
            }
        }
        cout << cost[V - 1];
    }
};
int main()
{
    int N, M, tax, u, v;
    cin >> N >> M;
    Graph graph(N);
    for (int i = 0; i < N; i++)
    {
        cin >> tax;
        graph.addTax(tax);
    }
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph.addEdge(u - 1, v - 1);
        graph.addEdge(v - 1, u - 1);
    }
    graph.dijkstra();
}