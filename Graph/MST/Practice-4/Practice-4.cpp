#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
#define pip pair<int, pair<int, int>>
int manhattanDistance(pii &u, pii &v)
{
    return abs(u.first - v.first) + abs(u.second - v.second);
}
int main()
{
    int n;
    cin >> n;
    vector<pii> vertices;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        vertices.push_back({x, y});
    }
    int cost = 0;
    map<pii, int> distance;
    map<pii, bool> visited;
    for (int i = 0; i < n; i++)
    {
        distance[vertices[i]] = INF;
        visited[vertices[i]] = false;
    }
    distance[vertices[0]] = 0;
    priority_queue<pip, vector<pip>, greater<pip>> pq;
    pq.push({distance[vertices[0]], vertices[0]});
    while (!pq.empty())
    {
        pii u = pq.top().second;
        int dist_u = pq.top().first;
        pq.pop();
        if (visited[u])
            continue;
        visited[u] = true;
        for (pii v : vertices)
        {
            if (!visited[v] && distance[v] > manhattanDistance(u, v))
            {
                distance[v] = manhattanDistance(u, v);
                pq.push({distance[v], v});
            }
        }
    }
    for (pii u : vertices)
    {
        cost += distance[u];
    }
    cout << cost;
}