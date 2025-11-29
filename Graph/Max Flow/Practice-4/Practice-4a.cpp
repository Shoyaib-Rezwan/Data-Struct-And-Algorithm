#include <bits/stdc++.h>
using namespace std;
bool bfs(vector<vector<int>> &rGraph, vector<int> &parent, int s, int t)
{
    int V = rGraph.size();
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    parent[s] = -2;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (parent[v] == -1 && rGraph[u][v])
            {
                parent[v] = u;
                if (v == t)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}
int fordFulkerson(vector<vector<int>> &rGraph, int s, int t)
{
    int maxFlow = 0;
    int V = rGraph.size();
    vector<int> parent(V, -1);
    while (bfs(rGraph, parent, s, t))
    {
        int f = INT32_MAX;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            f = min(f, rGraph[u][v]);
        }
        maxFlow += f;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= f;
            rGraph[v][u] += f;
        }
    }
    return maxFlow;
}
int main()
{
    int V, E;
    cin >> V >> E;
    vector<vector<int>> rGraph(V, vector<int>(V, 0)), original;
    for (int i = 0; i < E; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        rGraph[u - 1][v - 1] = c;
    }
    original = rGraph;
    int s, t;
    cin >> s >> t;
    s--;
    t--;
    int maxFlow = fordFulkerson(rGraph, s, t);
    int maxNode = -1, maxNodeFlow = -1;
    for (int u = 0; u < V; u++)
    {
        if (u == s || u == t)
            continue;
        int temp = 0;
        for (int v = 0; v < V; v++)
        {
            temp += original[u][v] ? original[u][v] - rGraph[u][v] : 0;
        }
        if (temp > maxNodeFlow)
        {
            maxNodeFlow = temp;
            maxNode = u + 1;
        }
    }
    cout << maxNode << ' ' << maxNodeFlow << '\n';
    // run bfs from the s... put all the nodes reachable from s to one part and the remaining nodes into the other parts
    queue<int> q;
    vector<bool> visited(V, false);
    visited[s] = true;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (!visited[v] && rGraph[u][v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    vector<int> left, right;
    for (int u = 0; u < V; u++)
    {
        if (visited[u])
            left.push_back(u + 1);
        else
            right.push_back(u + 1);
    }
    for (int x : left)
    {
        cout << x << ' ';
    }
    cout << '\n';
    for (int x : right)
    {
        cout << x << ' ';
    }
    cout << "\n"
         << maxFlow;
}