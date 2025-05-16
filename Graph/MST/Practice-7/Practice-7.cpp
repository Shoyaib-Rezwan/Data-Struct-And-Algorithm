// CSES problem: https://cses.fi/problemset/task/1675
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define ll long long
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
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<int> distance(n, INF);
    distance[0] = 0;
    pq.push({0, 0});
    vector<bool> visited(n, false);
    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (pii x : adj[u])
        {
            int v = x.first, w = x.second;
            if (!visited[v] && distance[v] > w)
            {
                distance[v] = w;
                pq.push({distance[v], v});
            }
        }
    }
    ll cost = 0;
    for (int i = 0; i < n; i++)
    {
        if (distance[i] == INF)
        {
            cost = -1;
            break;
        }
        cost += (ll)distance[i];
    }
    if (cost == -1)
        cout << "IMPOSSIBLE";
    else
        cout << cost;
}