#include <bits/stdc++.h>
#define INF INT32_MAX
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
    int n;
    cin >> n;
    vector<string> team(n);
    vector<int> win(n);
    vector<vector<int>> games(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        int lost, left;
        cin >> team[i] >> win[i] >> lost >> left;
        for (int j = 0; j < n; j++)
        {
            cin >> games[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        int gameCount = 0;
        int gameLeft = 0;
        bool eliminated = false;
        for (int j = 0; j < n; j++)
        {
            gameLeft += games[i][j];
        }
        for (int j = 0; j < n; j++)
        {
            if (win[j] > win[i] + gameLeft)
            {
                cout << team[i] << '\n';
                eliminated = true;
                break;
            }
        }
        if (eliminated)
            continue;
        vector<pair<int, int>> gameNodes;
        for (int u = 0; u < n; u++)
        {
            if (u == i)
                continue;
            for (int v = u + 1; v < n; v++)
            {
                if (v == i)
                    continue;
                if (games[u][v])
                    gameNodes.push_back({u, v});
            }
        }
        int g = gameNodes.size();
        int V = g + n + 2;
        int s = V - 2, t = V - 1;
        vector<vector<int>> rGraph(V, vector<int>(V, 0));
        for (int v = 0; v < g; v++)
        {
            int t1 = gameNodes[v].first;
            int t2 = gameNodes[v].second;
            rGraph[s][v] = games[t1][t2];
            gameCount += games[t1][t2];
        }
        for (int u = 0; u < g; u++)
        {
            int v1 = gameNodes[u].first, v2 = gameNodes[u].second;
            rGraph[u][v1 + g] = rGraph[u][v2 + g] = INF;
        }
        for (int u = g; u < g + n; u++)
        {
            if (u == i + g)
                continue;
            rGraph[u][t] = win[i] + gameLeft - win[u - g];
        }
        int maxFlow = fordFulkerson(rGraph, s, t);
        if (maxFlow < gameCount)
        {
            cout << team[i] << '\n';
        }
    }
}