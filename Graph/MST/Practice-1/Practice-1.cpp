#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> distance(n);
    for (int i = 0; i < n; i++)
    {
        cin >> distance[i];
    }
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u - 1].push_back({v - 1, w});
        adj[v - 1].push_back({u - 1, w});
    }
    vector<bool> inMST(n, false);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for (int i = 0; i < n; i++)
    {
        pq.push({distance[i], i});
    }
    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (inMST[u])
            continue;
        inMST[u] = true;
        for (pii x : adj[u])
        {
            int v = x.first, w = x.second;
            if (!inMST[v] && distance[v] > w)
            {
                distance[v] = w;
                pq.push({distance[v], v});
            }
        }
    }
    int cost = 0;
    for (int i = 0; i < n; i++)
    {
        cost += distance[i];
    }
    cout << cost;
}