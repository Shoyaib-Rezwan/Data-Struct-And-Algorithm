#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    queue<int> q;
    vector<int> parent(n, -1);
    q.push(0);
    vector<bool> visited(n, false);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (visited[u])
        {
            continue;
        }
        visited[u] = true;
        for (int v : adj[u])
        {
            if (visited[v] && parent[u]!=v)
            {
                cout << "YES\n"
                     << u + 1 << ' ' << v + 1;
                return 1;
            }
            q.push(v);
            parent[v] = u;
        }
    }
    cout << "NO\n";
}