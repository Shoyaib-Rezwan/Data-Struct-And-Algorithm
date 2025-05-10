#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define vvi vector<vector<int>>
class Graph
{
    int V;
    vvi distance, prdecessor;

    void getPath(int u, int v, vector<int> &path)
    {
        if (u == v)
            path.push_back(u);
        else if (prdecessor[u][v] == -1)
            return;
        else
        {
            getPath(u, prdecessor[u][v], path);
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
        prdecessor.resize(V, vector<int>(V, -1));
    }
    void addEdge(int u, int v, int w)
    {
        distance[u][v] = w;
        prdecessor[u][v] = u;
    }
    void floyd_warshall()
    {
        for (int k = 0; k < V; k++) // int i = 0; i < V; i++
        {
            for ( int i = 0; i < V; i++)//int j = 0; j < V; j++
            {
                for (int j = 0; j < V; j++) // int k = 0; k < V; k++
                {
                    if (distance[i][k] != INF && distance[k][j] != INF)
                    {
                        if (distance[i][j] > distance[i][k] + distance[k][j])
                        {
                            distance[i][j] = distance[i][k] + distance[k][j];
                            prdecessor[i][j] = prdecessor[k][j];
                        }
                    }
                }
            }
        }
        for (int i = 0; i < V; i++)
        {
            cout << i + 1 << ": ";
            for (int j = 0; j < V; j++)
            {
                if (distance[i][j] == INF)
                    cout << j + 1 << "(" << "INF" << ") ";
                else
                    cout << j + 1 << "(" << distance[i][j] << ") ";
            }
            cout << '\n';
        }
        vector<int> path;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << i + 1 << "->" << j + 1 << ": ";
                path.clear();
                getPath(i, j, path);
                if (path.empty())
                    cout << "No path exists!\n";
                else
                {
                    for (int x : path)
                    {
                        cout << x + 1 << ' ';
                    }
                    cout << '\n';
                }
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