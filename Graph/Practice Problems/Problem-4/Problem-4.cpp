// #include <bits/stdc++.h>
// using namespace std;
// bool DFS(vector<vector<int>> &adj, int u, vector<char> &color, stack<int> &stk)
// {
//     color[u] = 'G';
//     for (int v : adj[u])
//     {
//         if (color[v] == 'G' && !DFS(adj, v, color, stk))
//             return false;
//     }
//     color[u] = 'B';
//     stk.push(u);
//     return true;
// }
// int main()
// {
//     int n, m;
//     cin >> n >> m;
//     vector<vector<int>> adj(n);
//     for (int i = 0; i < m; i++)
//     {
//         int u, v;
//         cin >> u >> v;
//         adj[u - 1].push_back(v - 1);
//     }
//     vector<char> color(n, 'W');
//     stack<int> stk;
//     for (int u = 0; u < n; u++)
//     {
//         if (color[u] == 'W')
//         {
//             if (!DFS(adj, u, color, stk))
//             {
//                 cout << "CYCLE DETECTED!!!";
//                 return -1;
//             }
//         }
//     }
//     vector<bool> processed(n, false);
//     while (!stk.empty())
//     {
//         int u = stk.top();
//         int count = 0;
//         stk.pop();
//         if (processed[u])
//             continue;
//         vector<pair<int, int>> workers;
//         workers.push_back({u, 0});
//         int level = 0;
//         queue<int> q;
//         q.push(u);
//         while (!q.empty())
//         {
//             int u = q.front();
//             q.pop();
//             if (processed[u])
//                 continue;
//             processed[u] = true;
//             for (int v : adj[u])
//             {
//                 if (!processed[v])
//                 {
//                     q.push(v);
//                     workers.push_back({v, level + 1});
//                     count++;
//                 }
//             }
//             level++;
//         }
//         cout << u << ' ' << count << '\n';
//         for (pair<int, int> x : workers)
//         {
//             cout << x.first + 1 << ' ' << x.second << '\n';
//         }
//     }
// }
#include <bits/stdc++.h>
using namespace std;
void DFS(vector<vector<int>> &adj, int u, stack<int> &stk, vector<bool> &visited)
{
    visited[u] = true;
    for (int v : adj[u])
    {
        if (!visited[v])
        {
            DFS(adj, v, stk, visited);
        }
    }
    stk.push(u);
}
void BFS(vector<vector<int>> &adj, int u, vector<bool> &visited, vector<int> &level, vector<int> &subOrdinates)
{
    level[u] = 0;
    queue<int> q;
    q.push(u);
    while (!q.empty())
    {
        u = q.front();
        q.pop();
        if (visited[u])
            return;
        visited[u] = true;
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                level[v] = level[u] + 1;
                q.push(v);
                subOrdinates.push_back(v);
            }
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
    }
    vector<bool> visited(n, false);
    stack<int> stk;
    for (int u = 0; u < n; u++)
    {
        if (!visited[u])
            DFS(adj, u, stk, visited);
    }
    fill(visited.begin(), visited.end(), false);
    vector<int> level(n, -1);
    vector<int> subOrdinates;
    while (!stk.empty())
    {
        int u = stk.top();
        stk.pop();
        subOrdinates.clear();
        BFS(adj, u, visited, level, subOrdinates);
        while (!stk.empty() && visited[stk.top()])
        {
            stk.pop();
        }
        cout << u + 1 << ' ' << subOrdinates.size() << '\n';
        for (int v : subOrdinates)
        {
            cout << v + 1 << ' ' << level[v] << '\n';
        }
    }
}