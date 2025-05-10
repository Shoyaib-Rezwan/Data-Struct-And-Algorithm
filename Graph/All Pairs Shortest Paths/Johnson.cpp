#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
#define pii pair<int, int>
#define vvi vector<vector<int>>
struct Edge
{
    int u, v, w;
};
class Graph
{
    int V;
    vector<vector<pii>> adj;
    vector<Edge> edges;
    vector<int> potentials;
    vvi distance, predecessor;

    bool bellman_ford()
    {
        // first add a dummy node V
        for (int i = 0; i < V; i++)
        {
            edges.push_back({V, i, 0});
        }
        potentials[V] = 0;
        // now run bellman_ford
        for (int i = 0; i < V; i++)
        {
            for (Edge e : edges)
            {
                if (potentials[e.u] < INF && potentials[e.v] > potentials[e.u] + e.w)
                {
                    potentials[e.v] = potentials[e.u] + e.w;
                }
            }
        }
        // check for negative edges
        for (Edge e : edges)
        {
            if (potentials[e.u] < INF && potentials[e.v] > potentials[e.u] + e.w)
            {
                return false;
            }
        }
        return true;
    }

    void dijkstra(int s)
    {
        distance[s][s] = 0;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, s});
        while (!pq.empty())
        {
            int u = pq.top().second;
            int curr_dist = pq.top().first;
            pq.pop();
            if (distance[s][u] < curr_dist)
                continue;
            for (pii x : adj[u])
            {
                if (distance[s][x.first] > distance[s][u] + x.second)
                {
                    distance[s][x.first] = distance[s][u] + x.second;
                    predecessor[s][x.first] = u;
                    pq.push({distance[s][x.first], x.first});
                }
            }
        }
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

public:
    Graph(int V)
    {
        this->V = V;
        adj.resize(V);
        potentials.resize(V + 1, INF); // make the size 1 larger for placing the dummy variable
        distance.resize(V, vector<int>(V, INF));
        predecessor.resize(V, vector<int>(V, -1));
    }
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        edges.push_back({u, v, w});
    }
    void Solution()
    {
        // run bellman_ford
        bool check = bellman_ford();
        if (!check)
        {
            cout << "Negative weight cycle ditected!!";
            return;
        }
        // reweight the edges to remove all negative edges
        for (int u = 0; u < V; u++)
        {
            for (pii &x : adj[u])
            {
                x.second = x.second + potentials[u] - potentials[x.first];
            }
        }
        // run dijkstra from every vertex
        for (int i = 0; i < V; i++)
        {
            dijkstra(i);
        }

        // now retrieve all the distances as we have reweight the edges
        for (int u = 0; u < V; u++)
        {
            for (int v = 0; v < V; v++)
            {
                if (distance[u][v] < INF)
                    distance[u][v] = distance[u][v] - potentials[u] + potentials[v];
            }
        }

        // print distance of every vertex from every other.
        for (int u = 0; u < V; u++)
        {
            cout << u + 1 << ": ";
            for (int v = 0; v < V; v++)
            {
                if (distance[u][v] == INF)
                {
                    cout << v + 1 << "(" << "INF" << ") ";
                    continue;
                }
                cout << v + 1 << "(" << distance[u][v] << ") ";
            }
            cout << '\n';
        }
        // print path for every vertex to vertex
        vector<int> path;
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                cout << i + 1 << "->" << j + 1 << ": ";
                path.clear();
                getPath(i, j, path);
                if (path.empty())
                {
                    cout << "No path Exists!!" << '\n';
                    continue;
                }
                for (int x : path)
                {
                    cout << x + 1 << ' ';
                }
                cout << '\n';
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
    // cout << "Hello!\n";
    graph.Solution();
}