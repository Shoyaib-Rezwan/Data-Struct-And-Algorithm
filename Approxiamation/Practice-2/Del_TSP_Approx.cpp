#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
// example: Dasgupta page 178
//  input:
//   5
//   0 2 2 1 4
//   2 0 3 2 3
//   2 3 0 2 2
//   1 2 2 0 4
//   4 3 2 4 0
void getPreorder(vector<vector<int>> &adj, vector<int> &vertices, int u)
{
    vertices.push_back(u);
    for (int v : adj[u])
    {
        getPreorder(adj, vertices, v);
    }
}
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> distance(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> distance[i][j];
        }
    }
    // find the MST using PRIM consider 0 as the root
    vector<vector<int>> tree(n);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, 0});
    vector<bool> visited(n, false);
    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    dist[0] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        // build the tree
        if (parent[u] != -1)
        {
            tree[parent[u]].push_back(u);
        }
        for (int v = 0; v < n; v++)
        {
            if (v == u)
                continue;
            if (!visited[v] && dist[v] > distance[u][v])
            {
                dist[v] = distance[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    vector<int> preorder;
    getPreorder(tree, preorder, 0);
    // now find the approximated minCost and the path
    int minCost = 0;
    for (int i = 0; i < preorder.size(); i++)
    {
        minCost += distance[preorder[i]][preorder[(i + 1) % preorder.size()]];
    }
    cout << minCost << '\n';
    for (int x : preorder)
    {
        cout << x << ' ';
    }
    cout << 0 << '\n';
}