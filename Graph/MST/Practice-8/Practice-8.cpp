// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
#include <bits/stdc++.h>
using namespace std;
class Disjoint_Set
{
    int n;
    vector<int> parent, rank;

public:
    Disjoint_Set(int n)
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
        {
            parent[parenty] = parentx;
            return;
        }
        parent[parentx] = parenty;
        if (rank[parentx] == rank[parenty])
            rank[parenty]++;
    }
};
class Solution
{
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>> &edges)
    {
        Disjoint_Set alice(n), bob(n);
        int edgeRequire = 0;
        // first add the type 3 edges
        for (vector<int> x : edges)
        {
            int t = x[0], u = x[1], v = x[2];
            if (t == 3 && (alice.find(u) != alice.find(v) || bob.find(u) != bob.find(v)))
            {
                if (alice.find(u) != alice.find(v))
                {
                    alice.unite(u, v);
                }
                if (bob.find(u) != bob.find(v))
                {
                    bob.unite(u, v);
                }
                edgeRequire++;
            }
        }
        // check for the type-1 edges
        for (vector<int> x : edges)
        {
            int t = x[0], u = x[1] - 1, v = x[2] - 1;
            if (t == 1 && (alice.find(u) != alice.find(v)))
            {
                alice.unite(u, v);
                edgeRequire++;
            }
        }
        // check for the type-2 edges
        for (vector<int> x : edges)
        {
            int t = x[0], u = x[1] - 1, v = x[2] - 1;
            if (t == 2 && (bob.find(u) != bob.find(v)))
            {
                bob.unite(u, v);
                edgeRequire++;
            }
        }
        // check for connectivity
        bool connected = true;
        for (int u = 0; u < n - 1; u++)
        {
            if (alice.find(u) != alice.find(u + 1) || bob.find(u) != bob.find(u + 1))
            {
                connected = false;
                break;
            }
        }
        if(!connected)
            return -1;
        return edges.size() - edgeRequire;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges;
    for (int i = 0; i < m; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;
        edges.push_back({t, u, v});
    }
}