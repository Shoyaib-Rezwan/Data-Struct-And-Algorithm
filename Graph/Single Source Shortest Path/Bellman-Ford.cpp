/*

Input:
1st line is V E s (vertex, edge number, source)
next E lines contains directed edges with weights: u v w

Output:
output minimum distance from the source to every other nodes

Input:
5 5 0
1 2 5
0 1 -1
0 2 5
1 3 6
2 4 -2

Output=>
0: 0
1: -1
2: 4
3: 5
4: 2

Input:
5 8 0
0 1 -1
0 2 4
1 2 3
1 3 2
1 4 2
3 2 5
3 1 1
4 3 -3

Output=>
0: 0
1: -1
2: 2
3: -2
4: 1

Input:(Cormen: 22-1)
5 10 0
0 1 6
0 4 7
1 2 5
1 3 -4
1 4 8
2 1 -2
3 0 2
4 2 -3
3 2 7
4 3 9

Output=>
0: 0
1: 2
2: 4
3: -2
4: 7

Input:
5 7 4
0 1 5
1 2 3
2 3 -6
3 2 7
3 1 3
3 0 -3
4 0 10

Output=>
Negative Weight Cycle Exists!!!

*/
#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT_MAX
struct Edge
{
    int u, v, w;
    Edge(int u, int v, int w) : u(u), v(v), w(w) {}
};
class Graph
{
    int V, E, s;
    vector<Edge> edges;
    vector<int> distance;

public:
    Graph(int V, int s)
    {
        this->V = V;
        this->s = s;
        distance.resize(V, INF);
        distance[s] = 0;
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back(Edge(u, v, w));
    }
    void bellman_ford()
    {
        for (int i = 0; i < V - 1; i++)
        {
            for (Edge e : edges)
            {
                if (distance[e.u] != INF && distance[e.v] > distance[e.u] + e.w)
                {
                    distance[e.v] = distance[e.u] + e.w;
                }
            }
        }

        // detect the negative weight cycle
        for (Edge e : edges)
        {
            if (distance[e.u] != INF && distance[e.v] > distance[e.u] + e.w)
            {
                cout << "Negative Weight Cycle Exists!!!";
                return;
            }
        }
        for (int i = 0; i < V; i++)
        {
            cout << i << ": " << distance[i] << '\n';
        }
    }
};
int main()
{
    int V, E, s, u, v, w;
    cin >> V >> E >> s;
    Graph graph(V, s);
    for (int i = 0; i < E; i++)
    {
        cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }
    graph.bellman_ford();
}