// Suppose you are given a weighted DAG. Print the shortest path weight from each vertex to other vertices and also print the shortest paths.
#include <bits/stdc++.h>
using namespace std;
#define INF INT32_MAX
class Graph
{
    vector<vector<int>> distance;
    vector<vector<int>> predecessor;
    int n;

public:
    Graph(int V)
    {
        n = V;
        distance.resize(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++)
        {
            distance[i][i] = 0;
        }
        predecessor.resize(n, vector<int>(n, -1));
    }
    void addEdge(int u, int v, int w)
    {
        distance[u][v] = w;
        predecessor[u][v] = u;
    }
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
    void floyd_warshall()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (distance[i][k] != INF && distance[k][j] != INF)
                    {
                        if (distance[i][j] > distance[i][k] + distance[k][j])
                        {
                            distance[i][j] = distance[i][k] + distance[k][j];
                            predecessor[i][j] = predecessor[k][j];
                        }
                    }
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            cout << i + 1 << ": ";
            for (int j = 0; j < n; j++)
            {
                if (distance[i][j] == INF)
                    cout << j + 1 << "(INF) ";
                else
                    cout << j + 1 << "(" << distance[i][j] << ") ";
            }
        }
        vector<int> path;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                getPath(i, j, path);
                cout << i + 1 << "->" << j + 1 << ": ";
                if (path.size() == 0)
                {
                    cout << "No path exists!!\n";
                    continue;
                }
                for (int x : path)
                {
                    cout << x << ' ';
                }
                cout << '\n';
                path.clear();
            }
        }
    }
};
int main()
{
    int V, E, u, v, w;
    cin >> V >> E;
    Graph graph(V);
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u - 1, v - 1, w);
    }
    graph.floyd_warshall();
}