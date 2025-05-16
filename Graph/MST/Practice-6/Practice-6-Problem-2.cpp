#include <bits/stdc++.h>
using namespace std;
struct Edge
{
    int u, v, w;
};
struct comperator
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
    sort(edges.begin(), edges.end(), comperator());
}