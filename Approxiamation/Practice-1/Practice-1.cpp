#include <bits/stdc++.h>
#define INF INT32_MAX
using namespace std;
void approxKnapsack(float eps, vector<int> &weights, vector<int> &values, int W, int originalInstance)
{
    int n = weights.size();
    int V = 0;
    int vmax = 0;
    for (int x : values)
    {
        vmax = max(vmax, x);
    }
    cout << vmax << '\n';
    float theta = (eps * vmax) / ((n * 1.0) * 2);
    vector<int> tempValues;
    for (int x : values)
    {
        tempValues.push_back((x * 1.0) / theta);
        V += (x * 1.0) / theta;
    }
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, INF));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            dp[i][j] = min(dp[i - 1][j], (j >= tempValues[i - 1] && dp[i - 1][j - tempValues[i - 1]] < INF) ? dp[i - 1][j - tempValues[i - 1]]+weights[i-1] : INF);
        }
    }
    int usedWeights = 0, j, i = n, roundedValue = 0, originalValue = 0;
    ;
    for (j = V; j >= 0; j--)
    {
        if (dp[i][j] <= W)
        {
            usedWeights = dp[i][j];
            break;
        }
    }
    roundedValue = j;
    vector<int> objects;
    while (i && j)
    {
        if (dp[i][j] == dp[i - 1][j])
        {
            i--;
        }
        else
        {
            objects.push_back(i);
            originalValue += values[i - 1];
            j = j - tempValues[i - 1];
            i--;
        }
    }
    cout << "Rounded Instance with Eps: " << eps << '\n';
    cout << "Theta: " << theta << '\n';
    cout << "Answer of reduced instance: " << roundedValue << '\n';
    cout << "Answer of reduced instance multiplied by theta: " << roundedValue * theta << '\n';
    cout << "Indices: ";
    for (int x : objects)
    {
        cout << x << ' ';
    }
    cout << '\n';
    cout << "Answer of original instance (rounded up): " << originalValue << '\n';
    cout << "Used Weight: " << usedWeights << '\n';
    cout << "Ratio: " << (originalInstance * 1.0) / originalValue << '\n';
}
int main()
{
    int n, W, V = 0;
    cin >> n >> W;
    vector<int> weights(n), values(n);
    for (int i = 0; i < n; i++)
    {
        cin >> values[i] >> weights[i];
        V += values[i];
    }
    // solving original instance
    vector<vector<int>> dp(n + 1, vector<int>(V + 1, INF));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            dp[i][j] = min(dp[i - 1][j], (values[i - 1] > j || dp[i - 1][j - values[i - 1]] == INF) ? INF : dp[i - 1][j - values[i - 1]] + weights[i - 1]);
        }
    }
    int usedWeight = 0, j, i = n, totalValue = 0;
    for (j = V; j >= 0; j--)
    {
        if (dp[n][j] <= W)
        {
            usedWeight = dp[n][j];
            break;
        }
    }
    totalValue = j;
    vector<int> objects;
    while (i && j)
    {
        if (dp[i][j] == dp[i - 1][j])
            i--;
        else
        {
            objects.push_back(i);
            j = j - values[i - 1];
            i--;
        }
    }
    cout << "Original Instance: \n";
    cout << "Answer: " << totalValue << '\n';
    cout << "Used Weight: " << usedWeight << '\n';
    cout << "Indices: ";
    for (int x : objects)
    {
        cout << x << ' ';
    }
    cout << '\n';
    approxKnapsack(0.5, weights, values, W, totalValue);
    approxKnapsack(0.2, weights, values, W, totalValue);
    approxKnapsack(0.1, weights, values, W, totalValue);
    approxKnapsack(0.05, weights, values, W, totalValue);
}