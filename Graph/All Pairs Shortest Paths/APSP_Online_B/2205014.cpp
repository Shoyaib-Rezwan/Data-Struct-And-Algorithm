#include <bits/stdc++.h>
using namespace std;
#define INF INT32_MAX
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> distance(n, vector<int>(n, INF));
    vector<int> station(n), target(n);
    for (int i = 0; i < n; i++)
    {
        distance[i][i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> station[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> target[i];
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        distance[u - 1][v - 1] = w;
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
                }
            }
        }
    }
    int cost = 0;
    double rate = 0.5;
    vector<int> costs(n, 0);
    for (int i = 0; i < n; i++)
    {
        if (distance[station[i] - 1][target[i] - 1] != INF)
        {
            costs[i] = distance[station[i] - 1][target[i] - 1];
        }
    }
    sort(costs.begin(), costs.end());
    reverse(costs.begin(), costs.end());
    for (int i = 0; i < n; i++)
    {
        if (i % k == 0)
            rate *= 2;
        cost += costs[i] * (int)rate;
    }
    cout << cost;
}