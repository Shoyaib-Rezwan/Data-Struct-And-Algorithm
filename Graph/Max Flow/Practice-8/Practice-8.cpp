#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;
int getSize(string &a)
{
    if (a == "XXL")
        return 0;
    if (a == "XL")
        return 1;
    if (a == "L")
        return 2;
    if (a == "M")
        return 3;
    if (a == "S")
        return 4;
    else
        return 5;
}
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
    int t;
    cin >> t;
    for (int test = 1; test <= t; test++)
    {
        int n, m;
        cin >> n >> m;
        int V = 6 + m + 2, s = V - 2, t = V - 1;
        vector<vector<int>> rGraph(V, vector<int>(V, 0));
        for (int v = 0; v < 6; v++)
        {
            rGraph[s][v] = n;
        }
        for (int u = 6; u < 6 + m; u++)
        {
            rGraph[u][t] = 1;
        }
        for (int v = 6; v < 6 + m; v++)
        {
            string a, b;
            cin >> a >> b;
            int u1 = getSize(a), u2 = getSize(b);
            rGraph[u1][v] = 1;
            rGraph[u2][v] = 1;
        }
        int maxFlow = fordFulkerson(rGraph, s, t);
        cout << "Case-" << test << ": ";
        if (maxFlow < m)
        {
            cout << "Not ";
        }
        cout << "Possible\n";
    }
}