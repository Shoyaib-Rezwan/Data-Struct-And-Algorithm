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
    int m, n, x, y, p;
    cin >> m >> n >> x >> y >> p;
    int V = x + y + 2, s = V - 2, t = V - 1;
    vector<vector<int>> rGraph(V, vector<int>(V, 0));
    for (int i = 0; i < p; i++)
    {
        int u, v;
        cin >> u >> v;
        rGraph[u][v + x] = m;
    }
    for (int v = 0; v < x; v++)
    {
        rGraph[s][v] = n;
    }
    for (int u = x; u < x + y; u++)
    {
        rGraph[u][t] = n;
    }
    int maxFlow = fordFulkerson(rGraph, s, t);
    for (int u = 0; u < x; u++)
    {
        for (int v = x; v < x + y; v++)
        {
            if (rGraph[v][u])
            {
                cout << "( " << u << ", " << v - x << " )->" << rGraph[v][u] << " dances\n";
            }
        }
    }
}