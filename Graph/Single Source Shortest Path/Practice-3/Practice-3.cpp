#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
class Graph
{
    int V, flag;
    vector<vector<pii>> adj;
    vector<int> cost;
    map<string, int> mp;
    map<int, string> mp2;
    vector<int> parent;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
        parent.resize(V, -1);
        cost.resize(V, INF);
        flag = 0;
    }
    void addEdge(string u, string v, int c)
    {
        if (mp.find(u) == mp.end())
        {
            mp.insert({u, flag});
            mp2.insert({flag, u});
            flag++;
        }
        if (mp.find(v) == mp.end())
        {
            mp.insert({v, flag});
            mp2.insert({flag, v});
            flag++;
        }
        adj[mp[u]].push_back({mp[v], c});
        adj[mp[v]].push_back({mp[u], c});
    }
    void dijkstra(string s)
    {
        int src = mp[s];
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        cost[src] = 0;
        pq.push({0, src});
        int u, cost_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            cost_u = pq.top().first;
            pq.pop();
            if (cost[u] < cost_u)
                continue;
            for (pii x : adj[u])
            {
                if (cost[x.first] > cost[u] + x.second)
                {
                    parent[x.first] = u;
                    cost[x.first] = cost[u] + x.second;
                    pq.push({cost[x.first], x.first});
                }
            }
        }
    }
    void printPath(string u, int v = -2)
    {
        if (v == -2)
        {
            v = mp[u];
        }
        if (parent[v] != -1)
            printPath("", parent[v]);
        cout << mp2[v] << ' ';
    }
    void printPathRev(string u, int v = -2)
    {
        if (v == -2)
        {
            v = mp[u];
        }
        cout << mp2[v] << ' ';
        if (parent[v] != -1)
            printPathRev("", parent[v]);
    }
    int operator[](string u)
    {
        return cost[mp[u]];
    }
};
int main()
{
    int s1, r1, s2, r2;
    cin >> s1 >> r1 >> s2 >> r2;
    Graph g1(s1), g2(s2);
    string u, v;
    int c;
    for (int i = 0; i < r1; i++)
    {
        cin >> u >> v >> c;
        g1.addEdge(u, v, c);
    }
    for (int i = 0; i < r2; i++)
    {
        cin >> u >> v >> c;
        g2.addEdge(u, v, c);
    }
    int p1, p2;
    cin >> p1;
    vector<pair<string, int>> port1(p1);
    for (int i = 0; i < p1; i++)
    {
        cin >> port1[i].first >> port1[i].second;
    }
    cin >> p2;
    vector<pair<string, int>> port2(p2);
    for (int i = 0; i < p2; i++)
    {
        cin >> port2[i].first >> port2[i].second;
    }
    string src1, src2;
    cin >> src1 >> src2;
    g1.dijkstra(src1);
    g2.dijkstra(src2);
    int minCost = INF, pos1, pos2;
    for (int i = 0; i < p1; i++)
    {
        for (int j = 0; j < p2; j++)
        {
            if (port1[i].second + port2[j].second + g1[port1[i].first] + g2[port2[j].first] < minCost)
            {
                minCost = port1[i].second + port2[j].second + g1[port1[i].first] + g2[port2[j].first];
                pos1 = i;
                pos2 = j;
            }
        }
    }
    cout << minCost << '\n';
    g1.printPath(port1[pos1].first);
    g2.printPathRev(port2[pos2].first);
}