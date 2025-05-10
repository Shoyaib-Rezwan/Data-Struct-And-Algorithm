#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
struct state
{
    int city, fuel, cost;
    state(int city, int fuel, int cost) : city(city), fuel(fuel), cost(cost) {}

    bool operator<(const state &b) const
    {
        return cost > b.cost;
    }
};

class Graph
{
    int V, C;
    vector<int> fuelCost;
    vector<vector<pii>> adj;
    vector<vector<int>> minCost;

public:
    Graph(int V, int C)
    {
        this->V = V;
        this->C = C;
        adj.resize(V);
        minCost.resize(V, vector<int>(C + 1, INF));
    }
    void addfuelCost(int cost)
    {
        fuelCost.push_back(cost);
    }
    void addEdge(int u, int v, int c)
    {
        adj[u].push_back({v, c});
    }
    void modifiedDijkstra(int s, int d)
    {
        priority_queue<state> pq;
        pq.push(state(s, 0, 0));
        minCost[s][0] = 0;
        int city, fuel, cost;
        while (!pq.empty())
        {
            city = pq.top().city;
            fuel = pq.top().fuel;
            cost = pq.top().cost;
            pq.pop();
            if (cost > minCost[city][fuel])
                continue;
            if (city == d)
                break;
            if (fuel < C)
            {
                if (minCost[city][fuel + 1] > minCost[city][fuel] + fuelCost[city])
                {
                    minCost[city][fuel + 1] = minCost[city][fuel] + fuelCost[city];
                    pq.push(state(city, fuel + 1, minCost[city][fuel + 1]));
                }
            }
            for (pii x : adj[city])
            {
                if (fuel >= x.second)
                {
                    if (minCost[x.first][fuel - x.second] > minCost[city][fuel])
                    {
                        minCost[x.first][fuel - x.second] = minCost[city][fuel];
                        pq.push(state(x.first, fuel - x.second, minCost[x.first][fuel - x.second]));
                    }
                }
            }
        }
        if (city == d)
        {
            cout << cost << '\n';
        }
        else
        {
            cout << "Impossible";
        }
    }
};
int main()
{
    int n, m, c, price;
    cin >> n >> m >> c;
    Graph graph(n, c);
    for (int i = 0; i < n; i++)
    {
        cin >> price;
        graph.addfuelCost(price);
    }
    int a, b, p;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> p;
        graph.addEdge(a - 1, b - 1, p);
    }
    int s, d;
    cin >> s >> d;
    graph.modifiedDijkstra(s - 1, d - 1);
}