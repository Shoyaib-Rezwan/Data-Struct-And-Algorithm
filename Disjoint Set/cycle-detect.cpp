#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
class Disjoint_Set
{
    int n;
    vector<int> parent, rank;

public:
    Disjoint_Set(int n)
    {
        this->n = n;
        parent.resize(n, 0);
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
        else if (rank[parentx] > rank[parenty])
            parent[parenty] = parentx;
        else
        {
            parent[parentx] = parenty;
            if (rank[parentx] == rank[parenty])
                rank[parenty]++;
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Disjoint_Set dsu(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        if (dsu.find(u - 1) == dsu.find(v - 1))
        {
            cout << "Cycle Detected!";
            return 1;
        }
        dsu.unite(u - 1, v - 1);
    }
    cout << "No cycle detected!!!";
}