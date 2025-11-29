#include <bits/stdc++.h>
using namespace std;
void BFS(vector<vector<int>> &adj, int start, vector<int> &distance)
{
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (int v : adj[u])
        {
            if (visited[v])
                continue;
            distance[v] = distance[u] + 1;
            q.push(v);
        }
    }
}
int main()
{
    int n, m, q, minDist = INT32_MAX;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    vector<int> distance(n);
    distance[0] = 0;
    distance[1] = 0;
    BFS(adj, 0, distance);
    BFS(adj, 1, distance);
    cin >> q;
    pair<int, int> minPair = {-1, -1};
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        if (distance[u - 1] + distance[v - 1] < minDist)
        {
            minDist = distance[u - 1] + distance[v - 1];
            minPair = {u - 1, v - 1};
        }
    }
    cout << minPair.first + 1 << ' ' << minPair.second + 1 << '\n'
         << minDist + 1;
}