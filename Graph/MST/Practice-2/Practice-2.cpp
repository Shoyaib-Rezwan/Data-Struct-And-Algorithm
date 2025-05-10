#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define INF INT32_MAX
struct vertex
{
    int x, y, dist;
};
struct comparator
{
    bool operator()(const vertex &a, const vertex &b)
    {
        return a.dist > b.dist;
    }
};
int manhatton(pii a, pii b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}
int main()
{
    int n;
    cin >> n;
    vector<pii> house(n);
    for (int i = 0; i < n; i++)
    {
        cin >> house[i].first >> house[i].second;
    }
    map<pii, int> distance;
    map<pii, bool> visited;
    for (pii x : house)
    {
        distance.insert({{x.first, x.second}, INF});
        visited.insert({{x.first, x.second}, false});
    }
    distance[house[0]] = 0;
    priority_queue<vertex, vector<vertex>, comparator> pq;
    pq.push({house[0].first, house[0].second, 0});
    while (!pq.empty())
    {
        int x = pq.top().x, y = pq.top().y, dist = pq.top().dist;
        pq.pop();
        if (visited[{x, y}])
            continue;
        visited[{x, y}] = true;
        for (pii h : house)
        {
            if (!visited[h] && distance[h] > manhatton({x, y}, h))
            {
                distance[h] = manhatton({x, y}, h);
                pq.push({h.first, h.second, distance[h]});
            }
        }
    }
    int cost = 0;
    for (auto p : distance)
    {
        cost += p.second;
    }
    cout << cost;
}