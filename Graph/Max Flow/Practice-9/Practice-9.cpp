#include <bits/stdc++.h>
using namespace std;
struct Team
{
    string name;
    int rank, city;
};
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
        int n, g;
        cin >> n >> g;
        vector<Team> teams(n);
        int V = n + 2, s = V - 2, t = V - 1;
        vector<vector<int>> rGraph(V, vector<int>(V, 0));
        for (int v = 0; v < n; v++)
        {
            rGraph[s][v] = g;
            rGraph[v][t] = g;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> teams[i].name >> teams[i].rank >> teams[i].city;
        }
        for (int u = 0; u < n; u++)
        {
            for (int v = 0; v < n; v++)
            {
                if (((teams[u].rank % 2) ^ (teams[v].rank % 2)) && (teams[u].city != teams[v].city))
                {
                    rGraph[u][v] = 1;
                }
            }
        }
        int maxFlow = fordFulkerson(rGraph, s, t);
        cout << "Case-" << test << ": ";
        if (maxFlow == n * g)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
}
/*
2
6 2
Arsenal 1 1
ManCity 2 2
Tottenham 3 1
ManU 4 2
Liverpool 5 4
Westham 6 3
6 2
Arsenal 1 1
ManCity 2 2
Tottenham 3 1
ManU 4 2
Liverpool 5 3
Chelsea 6 1
*/