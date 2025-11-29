#include <bits/stdc++.h>
using namespace std;
struct Person
{
    int exp, age, crecord, origin, wprof, trust, language;
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
        int m, n;
        cin >> m >> n;
        vector<Person> gang(m), bussiness(n);
        for (int i = 0; i < m; i++)
        {
            cin >> gang[i].exp >> gang[i].age >> gang[i].crecord >> gang[i].origin >> gang[i].wprof >> gang[i].trust >> gang[i].language;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> bussiness[i].exp >> bussiness[i].age >> bussiness[i].crecord >> bussiness[i].origin >> bussiness[i].wprof >> bussiness[i].trust >> bussiness[i].language;
        }
        int V = m + n + 2, s = V - 2, t = V - 1;
        vector<vector<int>> rGraph(V, vector<int>(V, 0));
        for (int v = 0; v < m; v++)
        {
            rGraph[s][v] = 1;
        }
        for (int u = m; u < m + n; u++)
        {
            rGraph[u][t] = 1;
        }
        for (int u = 0; u < m; u++)
        {
            for (int v = m; v < m + n; v++)
            {
                if (
                    abs(gang[u].exp - bussiness[v - m].exp) <= 12 &&
                    abs(gang[u].age - bussiness[v - m].age) <= 5 &&
                    gang[u].crecord == bussiness[v - m].crecord &&
                    gang[u].origin == bussiness[v - m].origin &&
                    (gang[u].wprof | bussiness[v - m].wprof) &&
                    (gang[u].trust + bussiness[v - m].trust) >= 10 &&
                    (gang[u].language & bussiness[v - m].language))
                {
                    rGraph[u][v] = 1;
                }
            }
        }
        cout << fordFulkerson(rGraph, s, t) << '\n';
    }
}