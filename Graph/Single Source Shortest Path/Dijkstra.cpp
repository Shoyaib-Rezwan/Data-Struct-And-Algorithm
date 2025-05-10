/*
You are given a weightd DAG along with a source. Find the shortest path distance of each vertes from that source

Input:
5 6 0
0 1 4
0 2 1
2 1 2
1 3 1
2 3 5
3 4 3

Output=>
0: 0
1: 3
2: 1
3: 4
4: 7

Input:(Cormen 22-3)
5 10 0
0 1 10
0 4 5
1 2 1
1 4 2
2 3 4
3 0 7
3 2 6
4 1 3
1 2 9
4 3 2

Output=>
0: 0
1: 8
2: 9
3: 7
4: 5

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

public:
    Graph(int V, int s) : V(V), s(s)
    {
        adj.resize(V);
        distance.resize(V, INF);
        distance[s] = 0;
    }
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
    }
    void dijkstra()
    {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, s});
        int u, dist_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            dist_u = pq.top().first;
            pq.pop();
            if (distance[u] < dist_u)
                continue;
            for (pii x : adj[u])
            {
                if (distance[x.first] > distance[u] + x.second)
                {
                    distance[x.first] = distance[u] + x.second;
                    pq.push({distance[x.first], x.first});
                }
            }
        }
        for (int i = 0; i < V; i++)
        {
            cout << i << ": ";
            if (distance[i] == INF)
            {
                cout << "INF\n";
            }
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
    graph.dijkstra();
}