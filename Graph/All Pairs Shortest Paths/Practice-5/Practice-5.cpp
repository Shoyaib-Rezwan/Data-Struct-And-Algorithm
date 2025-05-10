#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define vvi vector<vector<int>>
class Graph
{
    int V;
    vvi distance;

public:
    Graph(int V)
    {
        this->V = V;
        distance.resize(V, vector<int>(V, INF));
        for (int i = 0; i < V; i++)
        {
            distance[i][i] = 0;
        }
    }
    void addEdge(int u, int v, int w)
    {
        distance[u][v] = distance[v][u] = w;
    }
    void floyd_warshall(int minCost)
    {
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                for (int k = 0; k < V; k++)
                {
                    if (distance[i][k] != INF && distance[k][j] != INF)
                    {
                        if (distance[i][j] > distance[i][k] + distance[k][j])
                        {
                            distance[i][j] = distance[i][k] + distance[k][j];
                        }
                    }
                }
            }
        }
        int minCityTravel = INF, canGo = 0;
        vector<int> result;
        for (int i = 0; i < V; i++)
        {
            canGo = 0;
            for (int j = 0; j < V; j++)
            {
                if (i == j)
                    continue;
                if (distance[i][j] <= minCost)
                    canGo++;
            }
            if (minCityTravel > canGo)
            {
                minCityTravel = canGo;
                result = {i};
            }
            else if (minCityTravel == canGo)
            {
                result.push_back(i);
            }
        }
        for (int x : result)
        {
            cout << x + 1 << ' ';
        }
    }
};
int main()
{
    int V, E;
    cin >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph.addEdge(u - 1, v - 1, w);
    }
    int minCost;
    cin >> minCost;
    graph.floyd_warshall(minCost);
}