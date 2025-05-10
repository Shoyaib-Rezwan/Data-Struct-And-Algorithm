/*This Solution is incorrect */

#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define pid pair<int, double>
#define pdi pair<double, int>
#define INF INT32_MAX
class Graph
{
    int V;
    vector<vector<pid>> adj;
    // vector<vector<pid>> adjRev;
    vector<double> rates1;
    vector<double> rates2;
    vector<int> parent1;
    vector<int> parent2;

public:
    Graph(int V) : V(V)
    {
        adj.resize(V);
        // adjRev.resize(V);
        rates1.resize(V, -1);
        rates2.resize(V, -1);
        parent1.resize(V, -1);
        parent2.resize(V, -1);
    }
    void addEdge(int u, int v, double r)
    {
        adj[u].push_back({v, r});
    }
    void dijkstra(int s, int d, vector<double> &rates, vector<int> &parent)
    {
        rates[s] = 1;
        priority_queue<pdi, vector<pdi>, less<pdi>> pq;
        pq.push({1, s});
        int u, rate_u;
        while (!pq.empty())
        {
            u = pq.top().second;
            rate_u = pq.top().first;
            pq.pop();
            if (rates[u] > rate_u)
            {
                continue;
            }
            for (pid x : adj[u])
            {
                if (rates[x.first] < rates[u] * x.second)
                {
                    rates[x.first] = rates[u] * x.second;
                    parent[x.first] = u;
                    pq.push({rates[x.first], x.first});
                }
            }
        }
    }
    void solution(int s, int d)
    {
        // dijkstra(s, d, rates1, parent1);
        dijkstra(d, s, rates2, parent2);
        cout << rates1[d] << ' ' << rates2[s] << '\n';
        if (rates1[d] * rates2[s] > 1)
        {
            cout << "There Exists Anomalities\n";
            return;
        }
        else
        {
            cout << "There Exists no Anomalities\n";
            cout << rates1[d];
            for (auto x : rates2)
            {
                cout << x << ' ';
            }
        }
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    int u, v;
    double r;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> r;
        graph.addEdge(u, v, r);
    }
    int s, d;
    cin >> s >> d;
    graph.solution(s, d);
}