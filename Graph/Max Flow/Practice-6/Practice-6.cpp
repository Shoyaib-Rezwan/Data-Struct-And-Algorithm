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
    int n, m;
    cin >> n >> m;
    vector<vector<int>> stickers(n + 1, vector<int>(m, 0));
    for (int i = 0; i < n + 1; i++)
    {
        int count;
        cin >> count;
        for (int j = 0; j < count; j++)
        {
            int num;
            cin >> num;
            stickers[i][num - 1]++;
        }
    }
    int V = n + m + 2, s = V - 2, t = V - 1;
    vector<vector<int>> rGraph(V, vector<int>(V, 0));
    for (int v = 0; v < m; v++)
    {
        rGraph[s][v] = stickers[0][v];
        rGraph[v][t] = 1;
    }
    for (int u = 0; u < m; u++)
    {
        for (int v = m; v < n + m; v++)
        {
            if (!stickers[v - m + 1][u])
                rGraph[u][v] = 1;
            else
                rGraph[v][u] = stickers[v - m + 1][u] - 1;
        }
    }
    vector<vector<int>> original = rGraph;
    int maxFlow = fordFulkerson(rGraph, s, t);
    cout << maxFlow << '\n';
    bool exchange = false;
    for (int f = 0; f < n; f++)
    {
        vector<int> give, take;
        for (int s = 0; s < m; s++)
        {
            if (original[s][f + m] && !rGraph[s][f + m])
            {
                give.push_back(s + 1);
                exchange = true;
            }
            if (original[f + m][s] > rGraph[f + m][s])
            {
                int sTaken = original[f + m][s] - rGraph[f + m][s];
                for (int i = 0; i < sTaken; i++)
                {
                    take.push_back(s + 1);
                }
            }
        }
        for (int i = 0; i < give.size(); i++)
        {
            cout << "Exchange a sticker with number " << give[i] << " against a sticker with number " << take[i] << " of friend " << f+1 << '\n';
        }
    }
    if (!exchange)
    {
        cout << "No exchange is possible";
    }
}