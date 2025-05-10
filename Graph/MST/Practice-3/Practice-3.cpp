#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define pid pair<int, double>
#define pdi pair<double, int>
int main()
{
    int n, m;
    double q;
    cin >> n >> m >> q;
    vector<vector<pid>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        double d;
        cin >> u >> v >> d;
        d = min(d, q);
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    }
    double cost = 0;
    priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
    vector<double> distance(n, INF);
    distance[0] = 0;
    vector<bool> visited(n, false);
    pq.push({0, 0});
    while (!pq.empty())
    {
        int u = pq.top().second;
        double curr_cost = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (pid x : adj[u])
        {
            int v = x.first;
            double d = x.second;
            if (!visited[v] && distance[v] > d)
            {
                distance[v] = d;
                pq.push({d, v});
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        cost += (distance[i] == INF) ? q : distance[i];
    }
    cout << cost;
}