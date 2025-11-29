// https://www.youtube.com/watch?v=cY4HiiFHO1o
// https://www.youtube.com/results?search_query=travelling+salesman+problem+code

// input:
//  4
//  0 10 15 20
//  5 0 9 10
//  6 13 0 12
//  8 8 9 0

// example: Dasgupta page 178
//  input:
//   5
//   0 2 2 1 4
//   2 0 3 2 3
//   2 3 0 2 2
//   1 2 2 0 4
//   4 3 2 4 0

// output:
// 0 1 4 2 3 0 //cycle
// 10 //mincost

#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;
// returns the indices that have been 1
set<int> getIndices(int j)
{
    set<int> result;
    for (int i = 0; i < 32; i++)
    {
        if (j & (1 << i))
        {
            result.insert(i);
        }
    }
    return result;
}
int main()
{
    int n;
    cin >> n;
    vector<vector<int>> distance(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> distance[i][j];
        }
    }
    // calculate number of subsets
    int subSetNo = (int)pow(2, n);
    // create a dp table
    vector<vector<int>> dp(n, vector<int>(subSetNo, INF));
    // 1 length tour-> 0 is the starting vertex
    dp[0][1] = 0;
    // 2 length tour
    for (int i = 1; i < n; i++)
    {
        dp[i][1 << i | 1 << 0] = distance[i][0];
    }
    // multilength tours
    for (int len = 3; len <= n; len++)
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < subSetNo; j++)
            {
                set<int> result = getIndices(j);
                if (result.size() == len - 1 && result.find(0) != result.end() && result.find(i) == result.end())
                {
                    for (int x : result)
                    {
                        if (x == 0)
                            continue;
                        dp[i][j | 1 << i] = min(dp[i][j | 1 << i], dp[x][j] + distance[i][x]);
                    }
                }
            }
        }
    }
    int minCost = INF, prev = -1;
    vector<int> objects;
    for (int i = 1; i < n; i++)
    {
        if (minCost > dp[i][subSetNo - 1] + distance[0][i])
        {
            minCost = dp[i][subSetNo - 1] + distance[0][i];
            prev = i;
        }
    }
    objects.push_back(0);
    objects.push_back(prev);
    int subSet = (subSetNo - 1) ^ (1 << prev);
    while (subSet)
    {
        for (int i = 0; i < n; i++)
        {
            if (dp[i][subSet] != INF && dp[prev][subSet | (1 << prev)] == distance[prev][i] + dp[i][subSet])
            {
                objects.push_back(i);
                subSet = subSet ^ (1 << i);
                prev = i;
                break;
            }
        }
    }
    for (int x : objects)
    {
        cout << x << ' ';
    }
    cout << '\n'
         << minCost;
}