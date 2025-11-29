#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;

int V, source, sink;
/*
input:
6 8
0 1 16
0 2 13
1 3 12
1 2 6
3 2 9
2 4 4
4 5 4
3 5 20
0 5

*/
bool BFS(vector<int> &parent, vector<vector<int>> &rGraph)
{
    queue<int> q;
    q.push(source);
    parent[source] = -2;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (parent[v] == -1 && rGraph[u][v] != 0)
            {
                parent[v] = u;
                if (v == sink)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}
int findMaxFlow(vector<int> &parent, vector<vector<int>> &rGraph)
{
    int maxFlow = 0;
    while (BFS(parent, rGraph))
    {
        int minCap = INF;
        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            minCap = min(minCap, rGraph[u][v]);
        }
        maxFlow += minCap;
        for (int v = sink; v != source; v = parent[v])
        {
            rGraph[parent[v]][v] -= minCap;
            rGraph[v][parent[v]] += minCap;
        }
        fill(parent.begin(), parent.end(), -1);
    }
    return maxFlow;
}
int main()
{
    int E;
    cin >> V >> E;
    vector<vector<int>> rGraph(V, vector<int>(V, 0));
    vector<int> parent(V, -1);
    for (int i = 0; i < E; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        rGraph[u][v] += c;
    }
    cin >> source >> sink;
    cout << findMaxFlow(parent, rGraph);
}