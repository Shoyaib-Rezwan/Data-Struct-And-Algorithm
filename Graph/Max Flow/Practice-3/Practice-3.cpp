#include <bits/stdc++.h>
using namespace std;
struct person
{
    int id, age, height;
};
bool bfs(vector<vector<int>> &rGraph, vector<int> &parent, int s, int t)
{
    int V = rGraph.size();
    queue<int> q;
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (parent[v] == -1 && rGraph[u][v] != 0)
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
    int f = 0;
    int V = rGraph.size();
    vector<int> parent(V, -1);
    while (bfs(rGraph, parent, s, t))
    {
        int curr_f = INT32_MAX;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            curr_f = min(curr_f, rGraph[u][v]);
        }
        f += curr_f;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v] -= curr_f;
            rGraph[v][u] += curr_f;
        }
    }
    return f;
}
int main()
{
    int m, n;
    cin >> m >> n;
    vector<person> men(m), women(n);
    for (int i = 0; i < m; i++)
    {
        cin >> men[i].height >> men[i].age >> men[i].id;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> women[i].height >> women[i].age >> women[i].id;
    }
    int v = n + m + 2, s = n + m, t = n + m + 1;
    vector<vector<int>> rGraph(v, vector<int>(v, 0));
    for (int v = 0; v < m; v++)
    {
        rGraph[s][v] = 1;
    }
    for (int u = m; u < n + m; u++)
    {
        rGraph[u][t] = 1;
    }
    for (int u = 0; u < m; u++)
    {
        for (int v = m; v < n + m; v++)
        {
            if (abs(men[u].height - women[v - m].height) <= 10 && abs(men[u].age - women[v - m].age) <= 5)
            {
                rGraph[u][v] = 1;
            }
        }
    }
    cout << fordFulkerson(rGraph, s, t) << '\n';
    for (int u = 0; u < m; u++)
    {
        for (int v = m; v < n + m; v++)
        {
            if (rGraph[v][u] == 1)
            {
                cout << "Man " << u + 1 << "- Woman " << v - m + 1 << '\n';
                break;
            }
        }
    }
}