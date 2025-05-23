
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
        edges.push_back({u - 1, v - 1, w, i});
    }
    sort(edges.begin(), edges.end(), comparator());
    vector<string> result(m, "none"); // initialize every edge to none.
    // check whether an edge can be present in atleast one MST
    Disjoint_set dsu(n);
    int i = 0;
    while (i < m)
    {
        int j = i;
        // find the range of indices i to j for which all edges are of the same weight
        while (j < m && edges[j].w == edges[i].w)
        {
            j++;
        }
        // now check which edges can be added. Modify their catagory to 'ateast one'
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v, index = edges[k].index;
            if (dsu.find(u) != dsu.find(v))
            {
                result[index] = "atleast one";
            }
        }
        // after checking unite all the vertices connected by this particular group of vertices
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v;
            if (dsu.find(u) != dsu.find(v))
            {
                dsu.unite(u, v);
            }
        }
        i = j;
    }

    // among the edges there are some, which are present in all msts. find them
    dsu.clear();
    i = 0;
    while (i < m)
    {
        int j = i;
        // find the range of indices i to j for which all edges are of the same weight
        while (j < m && edges[j].w == edges[i].w)
        {
            j++;
        }
        map<pii, int> edgeCount;           // counts how many similar weight edge connects {rootu,rootv}
        map<pii, vector<int>> edgeIndices; // stores similar weight edge that connects {rootu,rootv}
        // here rootu and rootv are representatives of 2 previously components. We need only one edge to connect the two components. If there are multiple edges, then it's a must that all these edges are not a must to present in all msts.
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v, index = edges[k].index;
            int rootu = dsu.find(u), rootv = dsu.find(v);
            if (rootu != rootv)
            {
                // sort rootu and rootv otherwise the set may treat multiple same pairs as different keys
                if (rootu > rootv)
                    swap(rootu, rootv);
                edgeCount[{rootu, rootv}]++;
                edgeIndices[{rootu, rootv}].push_back(index);
            }
        }
        // track all the same weight edges that solely connects two diffrent components
        for (auto entity : edgeCount)
        {
            pii root = entity.first;
            int count = entity.second;
            if (count == 1)
            {
                result[edgeIndices[root][0]] = "any";
            }
        }
        // finally connect the vertices
        for (int k = i; k < j; k++)
        {
            int u = edges[k].u, v = edges[k].v;
            int rootu = dsu.find(u), rootv = dsu.find(v);
            if (rootu != rootv)
            {
                dsu.unite(u, v);
            }
        }
        i = j;
    }
    for (int i = 0; i < m; i++)
    {
        cout << result[i] << '\n';
    }
}