// The given problem is incomplete.... use this extra condition: a worker can do a task iff strenght(worker)>=strength(task)
#include <bits/stdc++.h>
using namespace std;
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
    int N, M;
    cin >> N >> M;
    vector<int> worker(N), task(M);
    for (int i = 0; i < N; i++)
    {
        cin >> worker[i];
    }
    for (int i = 0; i < M; i++)
    {
        cin >> task[i];
    }
    vector<vector<int>> rGraph(N + M + 2, vector<int>(N + M + 2, 0));
    int s = N + M, t = N + M + 1;
    for (int u = 0; u < N; u++)
    {
        rGraph[s][u] = 1;
    }
    for (int u = N; u < N + M; u++)
    {
        rGraph[u][t] = 1;
    }
    for (int u = 0; u < N; u++)
    {
        for (int v = N; v < N + M; v++)
        {
            if (worker[u] >= task[v-N])
            {
                rGraph[u][v] = 1;
            }
        }
    }
    cout << fordFulkerson(rGraph, s, t);
}