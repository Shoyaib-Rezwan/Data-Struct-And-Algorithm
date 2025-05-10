/*
9 13
1 2 4
2 3 8
3 4 7
4 5 9
5 6 10
4 6 14
3 6 4
2 8 11
8 9 7
9 3 2
9 7 6
8 7 1
7 6 2

output: 37
*/

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
struct Edge
{
    int u, v, w;
};
struct comparator
{
    bool operator()(const Edge &a, const Edge &b) const
    {
        return a.w < b.w;
    }
};

class Disjoint_set
{
    int n;
    vector<int> parent, rank;

public:
    Disjoint_set(int n)
    {
        this->n = n;
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    void unite(int x, int y)
    {
        int parentx = find(x), parenty = find(y);
        if (parentx == parenty)
            return;
        if (rank[parentx] > rank[parenty])
            parent[parenty] = parentx;
        else
        {
            parent[parentx] = parenty;
            if(rank[parentx]==rank[parenty])
                rank[parenty]++;
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Disjoint_set dsu(n);
    vector<Edge> edges;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w});
    }
    sort(edges.begin(), edges.end(), comparator());
    int cost = 0;
    for (Edge e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            dsu.unite(e.u, e.v);
            cost += e.w;
        }
    }
    cout << cost;
}