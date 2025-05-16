// same solution as the previous problem.
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
struct Edge
{
    int u, v, w;
    int index; // index of the edge
};
struct comparator
{
    bool operator()(Edge &a, Edge &b)
    {
        if (a.w != b.w)
            return a.w < b.w;
        if (a.u != b.u)
            return a.u < b.u;
        return a.v < b.v;
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
            if (rank[parentx] == rank[parenty])
                rank[parenty]++;
        }
    }
    void clear()
    {
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
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
        edges.push_back({u, v, w, i});
    }
    sort(edges.begin(), edges.end(), comparator());
    vector<string> result(m, "pseudo-critical");
    // group the edges based on similar weights. Then find out the edges that connects 2 different components only by themselves. They will be the critical edges.
    Disjoint_set dsu(n);
    int i = 0;
    while (i < m)
    {
        int j = i + 1;
        while (j < m && edges[i].w == edges[j].w)
        {
            j++;
        }
        map<pii, int> edgeCount;
        map<pii, vector<int>> edgeIndices;
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v, index = edges[k].index;
            int rootu = dsu.find(u), rootv = dsu.find(v);
            if (rootu != rootv)
            {
                if (rootu > rootv)
                    swap(rootu, rootv);
                edgeCount[{rootu, rootv}]++;
                edgeIndices[{rootu, rootv}].push_back(index);
            }
        }
        for (auto &entity : edgeCount)
        {
            pii root = entity.first;
            int count = entity.second;
            if (count == 1)
            {
                result[edgeIndices[root][0]] = "critical";
            }
        }
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v;
            dsu.unite(u, v);
        }
        i = j;
    }
    vector<int> tempResults;
    // collect the critical edges
    for (int i = 0; i < m; i++)
    {
        if (result[i] == "critical")
            tempResults.push_back(i);
    }
    cout << "Critical edges: [";
    for (int x : tempResults)
    {
        cout << x << ' ';
    }
    cout << "]\n";
    tempResults.clear();
    // collect the pseudocritical edges
    for (int i = 0; i < m; i++)
    {
        if (result[i] != "critical")
            tempResults.push_back(i);
    }
    cout << "Pseudo critical edges: [";
    for (int x : tempResults)
    {
        cout << x << ' ';
    }
    cout << "]\n";
}