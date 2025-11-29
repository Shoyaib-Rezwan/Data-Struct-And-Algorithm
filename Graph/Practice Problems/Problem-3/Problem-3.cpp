#include <bits/stdc++.h>
using namespace std;
// the following process is incorrect. See problem 4 for better topological sort with cycle handling
bool DFS(vector<vector<int>> &adj, int u, vector<bool> &visited, stack<int> &stk)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (visited[v] || !DFS(adj, v, visited, stk))
        {
            return false;
        }
    }
    stk.push(u);
    return true;
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<bool> visited(n, false);
    stack<int> stk;
    for (int u = 0; u < n; u++)
    {
        if (!visited[u] && !DFS(adj, u, visited, stk))
        {
            cout << "-1";
            return 1;
        }
    }
    while (!stk.empty())
    {
        cout << stk.top() << ' ';
        stk.pop();
    }
}