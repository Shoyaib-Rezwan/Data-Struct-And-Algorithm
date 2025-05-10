#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
class Graph
{
    int V, flag;
    vector<vector<pii>> adj;
    unordered_map<string, int> mp;
    unordered_map<int, string> mp2;
    vector<int> time;
    vector<int> layover;
    vector<int> parent;

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
        time.resize(V, INF);
        parent.resize(V, -1);
        flag = 0;
    }
    void addLayout(string u, int layover_time)
    {
        layover.push_back(layover_time);
        mp.insert({u, flag});
        mp2.insert({flag, u});
        flag++;
    }
    void addEdge(string u, string v, int t)
    {
        adj[mp[u]].push_back({mp[v], t});
        adj[mp[v]].push_back({mp[u], t});
    }
    void getPath(int u, vector<int> &path)
    {
        if (parent[u] != -1)
            getPath(parent[u], path);
        path.push_back(u);
    }
    void dijkstra(string s1, string s2)
    {
        int src = mp[s1], dst = mp[s2];
        time[src] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, src});
        int u, time_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            time_u = pq.top().first;
            pq.pop();
            if (time[u] < time_u)
                continue;
            for (pii x : adj[u])
            {
                if (time[x.first] > time[u] + x.second + layover[x.first])
                {
                    time[x.first] = time[u] + x.second + layover[x.first];
                    pq.push({time[x.first], x.first});
                    parent[x.first] = u;
                }
            }
        }
        cout << time[dst] << '\n';
        vector<int> path;
        getPath(dst, path);
        for (int i = 0; i < path.size() - 1; i++)
        {
            cout << mp2[path[i]] << "->";
        }
        cout << mp2[path[path.size() - 1]];
    }
};
int main()
{
    int n, f;
    cin >> n >> f;
    Graph graph(n);
    for (int i = 0; i < n; i++)
    {
        string s;
        int layover_time;
        cin >> s >> layover_time;
        graph.addLayout(s, layover_time);
    }
    for (int i = 0; i < f; i++)
    {
        string u, v;
        int c;
        cin >> u >> v >> c;
        graph.addEdge(u, v, c);
    }
    string src, dst;
    cin >> src >> dst;
    graph.dijkstra(src, dst);
}