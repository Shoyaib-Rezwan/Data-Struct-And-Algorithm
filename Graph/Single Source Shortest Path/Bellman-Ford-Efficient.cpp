/*
You are given a weighted DAG....

Input:
5 5 0
1 2 5
0 1 -1
0 2 5
1 3 6
2 4 -2

Output=>
0: 0
1: -1
2: 4
3: 5
4: 2

Input:(Cormen 22-2)
6 10 1
0 1 5
0 2 3
1 2 2
1 3 6
2 3 7
2 4 4
2 5 2
3 4 -1
3 5 1
4 5 -2

Output=>
0: INF
1: 0
2: 2
3: 6
4: 5
5: 3
*/
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
class Graph
{
    int V, s;
    vector<vector<pii>> adj;
    vector<int> distance;
    stack<int> vertexOrder;
    vector<bool> visited;

    void toposort(int u)
    {
        visited[u] = true;
        for (pii x : adj[u])
        {
            if (!visited[x.first])
            {
                toposort(x.first);
            }
        }
        vertexOrder.push(u);
    }

public:
    Graph(int V, int s)
    {
        this->V = V;
        this->s = s;
        adj.resize(V);
        distance.resize(V, INF);
        visited.resize(V, false);
        distance[s] = 0;
    }
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
    }
    void efficient_bellman_ford()
    {
        toposort(s);
        while (!vertexOrder.empty())
        {
            int u = vertexOrder.top();
            vertexOrder.pop();
            for (pii x : adj[u])
            {
                if (distance[x.first] > distance[u] + x.second)
                {
                    distance[x.first] = distance[u] + x.second;
                }
            }
        }
        for (int i = 0; i < V; i++)
        {
            cout << i << ": ";
            if (distance[i] == INF)
                cout << "INF" << '\n';
            else
                cout << distance[i] << '\n';
        }
    }
};
int main()
{
    int V, E, s, u, v, w;
    cin >> V >> E >> s;
    Graph graph(V, s);
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    graph.efficient_bellman_ford();
}