#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int u, v, w;
    // this part is really crucial
    bool operator<(const Edge &e) const
    {
        if (w != e.w)
            return w < e.w;
        if (u != e.u)
            return u < e.u;
        return v < e.v;
    }
};
struct comparator
{
    bool operator()(const Edge &a, const Edge &b)
    {
        if (a.w != b.w)
            return a.w < b.w;
        if (a.u != b.u)
            return a.u < b.u;
        return a.v < b.v;
    }
};
class Disjoint_Set
{
    int n;
    vector<int> parent, rank;

public:
    Disjoint_Set(int n)
    {
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
            parent[parentx] = parenty;
        if (rank[parentx] == rank[parenty])
            rank[parenty]++;
    }
};

/* globals*/
vector<Edge> edges;
int minWeight;
int n;
set<vector<Edge>> MSTS; // why we are using set here? This is to avoid containing same MSTs twice

int mstWeight(vector<Edge> &edges)
{
    int minWeight = 0;
    Disjoint_Set dsu(n);
    for (Edge e : edges)
    {
        if (dsu.find(e.u) != dsu.find(e.v))
        {
            dsu.unite(e.u, e.v);
            minWeight += e.w;
        }
    }
    return minWeight;
}

// current is the edges that have been inside a spanning tree, and curr_weight is the total weight of that tree
void findAllMST(int edgeIndex, vector<Edge> current, int curr_Weight, Disjoint_Set dsu)
{
    // check if current is a MST
    if (current.size() == n - 1 and curr_Weight == minWeight)
    {
        // push current inside MSTs
        MSTS.insert(current);
        return;
    }
    // if it has more than n-1 edges or it's weight exceeds the minWeight or edgeIndex is out of bound then neglect it
    if (current.size() > n - 1 || curr_Weight > minWeight || edgeIndex >= edges.size())
        return;
    // recursive call neglecting current Edge
    findAllMST(edgeIndex + 1, current, curr_Weight, dsu);
    //  try to add edge at edgeIndex to the current
    int u = edges[edgeIndex].u, v = edges[edgeIndex].v, w = edges[edgeIndex].w;
    if (dsu.find(u) != dsu.find(v))
    {
        dsu.unite(u, v);
        current.push_back({u, v, w});
        curr_Weight += w;
        // recursive call
        findAllMST(edgeIndex + 1, current, curr_Weight, dsu);
    }
}
int main()
{
    int m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    // sort the edges in ascending order of the weights.
    sort(edges.begin(), edges.end(), comparator());

    // find the minimum mst weight
    minWeight = mstWeight(edges);

    // now generate all the mst:
    Disjoint_Set dsu(n);
    findAllMST(0, {}, 0, dsu);

    // now print all MST
    int count = 1;
    for (vector<Edge> e : MSTS)
    {
        cout << count++ << ": ";
        for (Edge edge : e)
        {
            cout << "[" << edge.u << ' ' << edge.v << ' ' << edge.w << ']' << ' ';
        }
        cout << '\n';
    }
}