#include <bits/stdc++.h>
using namespace std;
bool bfs(vector<vector<int>> &rGraph, vector<int> &parent, int &s, int &t, int V)
{
    fill(parent.begin(), parent.end(), -1);
    queue<int> q;
    q.push(s);
    parent[s] = -2;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 0; v < V; v++)
        {
            if (parent[v] == -1 && rGraph[u][v] > 0)
            {
                parent[v] = u;
                if (v == t)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}
int findMaxMatch(vector<vector<int>> &rGraph, int &N, int &M)
{
    int s = N + M, t = N + M + 1;
    for (int v = 0; v < M; v++)
    {
        rGraph[s][v] = 1;
    }
    for (int v = M; v < N + M; v++)
    {
        rGraph[v][t] = 1;
    }
    vector<int> parent(N + M + 2);
    int maxMatch = 0;
    while (bfs(rGraph, parent, s, t, N + M + 2))
    {
        maxMatch++;
        for (int v = t; v != s; v = parent[v])
        {
            int u = parent[v];
            rGraph[u][v]--;
            rGraph[v][u]++;
        }
    }
    return maxMatch;
}
int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> rGraph(N + M + 2, vector<int>(N + M + 2, 0));
    fflush(stdin);
    for (int i = 0; i < M; i++)
    {
        string str;
        getline(cin, str);
        vector<int> nums;
        int pos = 0;
        while (pos < str.size())
        {
            if (str[pos] == ' ')
            {
                pos++;
                continue;
            }
            int start = pos;
            int end = pos;
            while (pos + 1 < str.size() && str[pos + 1] != ' ')
            {
                pos++;
                end++;
            }
            nums.push_back(stoi(str.substr(start, end - start + 1)));
            pos++;
        }
        int u = nums[0]-1;
        for (int i = 1; i < nums.size(); i++)
        {
            int v = nums[i]+M-1;
            rGraph[u][v] = 1;
        }
    }
    cout << findMaxMatch(rGraph, N, M);
}