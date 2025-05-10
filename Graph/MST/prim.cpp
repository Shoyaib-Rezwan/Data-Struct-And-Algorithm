#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> graph(n);
    vector<bool> visited(n, false);
    vector<int> distance(n, INF);
    distance[0] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
        graph[v - 1].push_back({u - 1, w});
    }
    int cost = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        cost += dist_u;
        visited[u] = true;
        for (pii x : graph[u])
        {
            if (!visited[x.first] && distance[x.first] > x.second)
            {
                distance[x.first] = x.second;
                pq.push({distance[x.first], x.first});
            }
        }
    }
    cout << cost;
}