#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
void getPath(vector<int> &parent, vector<int> &path, int d)
{
    if (parent[d] != -1)
        getPath(parent, path, parent[d]);
    path.push_back(d);
}
int main()
{
    int k, n, x;
    cin >> k >> n >> x;
    vector<vector<pair<int, pii>>> adj(n);
    for (int i = 0; i < x; i++)
    {
        int u, v, t, c;
        cin >> u >> v >> t >> c;
        u = u - 1;
        v = v - 1;
        adj[u].push_back({v, {t, c}});
        adj[v].push_back({u, {t, c}});
    }
    int s, d;
    cin >> s >> d;
    s--;
    d--;
    vector<int> totalCost(n, INF), timelost(n), parent(n, -1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    totalCost[s] = 0;
    timelost[s] = 0;
    pq.push({0, s});
    while (!pq.empty())
    {
        int u = pq.top().second;
        int cost_u = pq.top().first;
        pq.pop();
        if (cost_u > totalCost[u])
            continue;
        for (auto x : adj[u])
        {
            int v = x.first, t = x.second.first, c = x.second.second;
            if (totalCost[u] != INF && totalCost[v] > totalCost[u] + k * (t + 1) + c)
            {
                totalCost[v] = totalCost[u] + k * (t + 1) + c;
                parent[v] = u;
                timelost[v] = timelost[u] + t + 1;
                pq.push({totalCost[v], v});
            }
        }
    }
    if (totalCost[d] == INF)
    {
        cout << "Error";
    }
    else
    {
        vector<int> path;
        getPath(parent, path, d);
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << path[i]+1 << "->";
        }
        cout << *(path.end() - 1)+1<<' ';
        cout << timelost[d] - 1 << ' '<<totalCost[d]-k;
    }
}