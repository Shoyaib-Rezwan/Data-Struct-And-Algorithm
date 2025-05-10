#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT_MAX
class Graph
{
    int V;
    vector<vector<pii>> adj, revAdj;
    vector<int> time1, time2, parent1, parent2;

public:
    Graph(int V) : V(V)
    {
        adj.resize(V);
        revAdj.resize(V);
        time1.resize(V, INF);
        time2.resize(V, INF);
        parent2.resize(V, -1);
        parent1.resize(V, -1);
    }
    void addEdge(int u, int v, int t)
    {
        adj[u].push_back({v, t});
        revAdj[v].push_back({u, t});
    }
    void dijkstra(int s, vector<int> &time, vector<int> &parent, vector<vector<pii>> &adj)
    {
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        time[s] = 0;
        pq.push({0, s});
        int u, time_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            time_u = pq.top().first;
            pq.pop();
            if (time[u] < time_u)
                continue;
            for (pii x : adj[u])
            {
                if (time[x.first] > time[u] + x.second)
                {
                    time[x.first] = time[u] + x.second;
                    pq.push({time[x.first], x.first});
                    parent[x.first] = u;
                }
            }
        }
    }
    void printPath(int u)
    {
        if (parent1[u] != -1)
            printPath(parent1[u]);
        cout << u << ' ';
    }
    void printPathRev(int u)
    {
        cout << u << ' ';
        if (parent2[u] != -1)
            printPathRev(parent2[u]);
    }
    void solution(int s)
    {
        dijkstra(s, time1, parent1, adj);
        dijkstra(s, time2, parent2, revAdj);
        int minTime = INF, minPos;
        for (int i = 0; i < V; i++)
        {
            if (i == s)
                continue;
            if (minTime > time1[i] + time2[i])
            {
                minTime = time1[i] + time2[i];
                minPos = i;
            }
        }
        cout << "Minimum total time: " << minTime
             << '\n';
        cout << "Paths:\n";
        printPath(minPos);
        cout << " (time: " << time1[minPos] << ")\n";
        printPathRev(minPos);
        cout << " (time: " << time2[minPos] << ")";
    }
};
int main()
{
    int s, r, u, v, t, f;
    cin >> s >> r;
    Graph graph(s);
    for (int i = 0; i < r; i++)
    {
        cin >> u >> v >> t;
        graph.addEdge(u, v, t);
    }
    cin >> f;
    graph.solution(f);
}