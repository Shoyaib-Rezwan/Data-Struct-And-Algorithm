#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }
    vector<bool> visited(n, false);
    vector<int> distance(n, INF);
    distance[0] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    int cost = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        cost += dist_u;
        for (pii x : adj[u])
        {
            int v = x.first;
            int w = x.second;
            if (!visited[v] && distance[v] > w)
            {
                distance[v] = w;
                pq.push({w, v});
            }
        }
    }
    cout << cost;
}