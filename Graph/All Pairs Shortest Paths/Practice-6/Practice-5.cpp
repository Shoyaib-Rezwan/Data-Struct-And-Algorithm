#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define NEGINF INT32_MIN
void getPath(vector<int> &path, vector<vector<int>> &parent, int s, int d)
{
    if (d != s)
    {
        getPath(path, parent, s, parent[s][d]);
    }
    path.push_back(d);
}
int main()
{
    int n, m, k, x;
    cin >> n >> m >> k >> x;
    vector<int> position(k), hourly_rate(k);
    vector<vector<pii>> adj(n);
    vector<vector<int>> distance(n, vector<int>(n, INF));
    vector<vector<int>> parent(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
    {
        distance[i][i] = 0;
    }
    for (int i = 0; i < k; i++)
    {
        cin >> position[i];
        position[i]--;
    }
    for (int i = 0; i < k; i++)
    {
        cin >> hourly_rate[i];
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        distance[u - 1][v - 1] = w;
        distance[v - 1][u - 1] = w;
        parent[u - 1][v - 1] = u - 1;
        parent[v - 1][u - 1] = v - 1;
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (distance[i][k] != INF && distance[k][j] != INF && distance[i][j] > distance[i][k] + distance[k][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    parent[i][j] = parent[k][j];
                }
            }
        }
    }
    // for (int i = 0;i<n;i++)
    // {
    //     for (int j = 0; j < n;j++)
    //     {
    //         cout << distance[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    // find the meeting city and total cost
    vector<int> totalCost(n, 0);
    for (int i = 0; i < k; i++)
    {
        int u = position[i];
        int c = hourly_rate[i];
        for (int v = 0; v < n; v++)
        {
            if (distance[u][v] == INF || totalCost[v] == INF)
                continue;
            if (distance[u][v] > x)
            {
                totalCost[v] = INF;
                continue;
            }
            totalCost[v] += distance[u][v] * c;
        }
    }
    int minCost = INF, meet;
    for (int u = 0; u < n; u++)
    {
        if (minCost > totalCost[u])
        {
            minCost = totalCost[u];
            meet = u;
        }
    }
    // find maxTraveltime
    int maxTravelTime = NEGINF;
    for (int i = 0; i < k; i++)
    {
        int u = position[i];
        if (distance[u][meet] > maxTravelTime)
        {
            maxTravelTime = distance[u][meet];
        }
    }
    cout << meet + 1 << ' ' << minCost << ' ' << maxTravelTime << '\n';
    // now print the paths
    for (int i = 0; i < k; i++)
    {
        int u = position[i];
        int c = hourly_rate[i];
        vector<int> path;
        getPath(path, parent, u, meet);
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i] + 1 << " -> ";
        }
        cout << path[path.size() - 1] + 1 << ' ' << distance[u][meet] * c << '\n';
    }
}