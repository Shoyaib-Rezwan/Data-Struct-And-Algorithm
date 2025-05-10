#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define vii vector<vector<int>>
#define pii pair<int, int>
class Graph
{
    int V, w1, w2, wallStreetCost;
    vii distance, predecessor;

    void getPath(int u, int v, vector<int> &path)
    {
        if (u == v)
            path.push_back(u);
        else if (predecessor[u][v] == -1)
            return;
        else
        {
            getPath(u, predecessor[u][v], path);
            path.push_back(v);
        }
    }

public:
    Graph(int V)
    {
        this->V = V;
        distance.resize(V, vector<int>(V, INF));
        for (int i = 0; i < V; i++)
        {
            distance[i][i] = 0;
        }
        predecessor.resize(V, vector<int>(V, -1));
    }
    void addEdge(int u, int v, int w)
    {
        distance[u][v] = w;
        distance[v][u] = w;
        predecessor[u][v] = u;
        predecessor[v][u] = v;
    }
    void floyd_warshall()
    {
        for (int k = 0; k < V; k++)
        {
            for (int u = 0; u < V; u++)
            {
                for (int v = 0; v < V; v++)
                {
                    if (distance[u][k] != INF && distance[k][v] != INF)
                    {
                        if (distance[u][v] > distance[u][k] + distance[k][v])
                        {
                            distance[u][v] = distance[u][k] + distance[k][v];
                            predecessor[u][v] = predecessor[k][v];
                        }
                    }
                }
            }
        }
    }
    void addWallStreet(int w1, int w2)
    {
        this->w1 = w1;
        this->w2 = w2;
        wallStreetCost = distance[w1][w2];
    }
    void findPath(int u, int v)
    {
        if (distance[u][w1] == INF || distance[w2][v] == INF)
        {
            cout << "No path from " << u + 1 << " to " << v + 1 << " through the Wall Street\n";
        }
        else
        {
            vector<int> path;
            if (distance[u][w1] + wallStreetCost + distance[w2][v] < distance[u][w2] + wallStreetCost + distance[w1][v])
            {
                cout << "Shortest Path Weight: " << distance[u][w1] + wallStreetCost + distance[w2][v] << '\n';
                getPath(u, w1, path);
                getPath(w2, v, path);
            }
            else
            {
                cout << "Shortest Path Weight: " << distance[u][w2] + wallStreetCost + distance[w1][v] << '\n';
                getPath(u, w2, path);
                getPath(w1, v, path);
            }
            for (int i = 0; i < path.size() - 1; i++)
            {
                cout << path[i] + 1 << "-> ";
            }
            cout << v + 1 << '\n';
        }
    }
};
int main()
{
    int n, m, u, v, w;
    cin >> n >> m;
    Graph graph(n);
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u - 1, v - 1, w);
    }
    int w1, w2;
    cin >> w1 >> w2;
    graph.addWallStreet(w1 - 1, w2 - 1);
    graph.floyd_warshall();
    while (true)
    {
        cin >> u >> v;
        if (u == -1)
            break;
        graph.findPath(u - 1, v - 1);
    }
}