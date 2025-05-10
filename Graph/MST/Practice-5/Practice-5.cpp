#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define NEGINF INT32_MIN
struct Edge
{
    int u, v, w;
};
struct comparator
{
    bool operator()(Edge &a, Edge &b)
    {
        return a.w > b.w;
    }
};
class DisjointSet
{
    int n;
    vector<int> parent, rank;

public:
    DisjointSet(int n)
    {
        this->n = n;
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
        rank.resize(n, 0);
    }
    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y)
    {
        int parentx = find(x), parenty = find(y);
        if (parentx == parenty)
            return;
        if (rank[x] > rank[y])
        {
            parent[parenty] = parentx;
            return;
        }
        parent[parentx] = parenty;
        if (rank[parentx] == rank[parenty])
            rank[parenty]++;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    sort(edges.begin(), edges.end(), comparator());
    DisjointSet dsu(n);
    int cost = 1;
    for (Edge e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            dsu.unite(e.u, e.v);
            cost *= e.w;
        }
    }
    cout << cost;
}