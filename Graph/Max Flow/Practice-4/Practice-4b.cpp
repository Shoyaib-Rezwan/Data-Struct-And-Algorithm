#include <bits/stdc++.h>
using namespace std;
struct person
{
    int height, age, divorced;
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
    int n, m;
    cin >> n >> m;
    vector<person> man(n), woman(m);
    for (int i = 0; i < n; i++)
    {
        cin >> man[i].height >> man[i].age >> man[i].divorced;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> woman[i].height >> woman[i].age >> woman[i].divorced;
    }
    int V = n + m + 2, s = V - 2, t = V - 1;
    vector<vector<int>> rGraph(V, vector<int>(V, 0));
    for (int v = 0; v < n; v++)
    {
        rGraph[s][v] = 1;
    }
    for (int v = n; v < n + m; v++)
    {
        rGraph[v][t] = 1;
    }
    for (int u = 0; u < n; u++)
    {
        for (int v = n; v < n + m; v++)
        {
            if (abs(man[u].height - woman[v - n].height) <= 10 && abs(man[u].age - woman[v - n].age) <= 5 && !(man[u].divorced ^ woman[v - n].divorced))
            {
                rGraph[u][v] = 1;
            }
        }
    }
    cout << fordFulkerson(rGraph, s, t);
}