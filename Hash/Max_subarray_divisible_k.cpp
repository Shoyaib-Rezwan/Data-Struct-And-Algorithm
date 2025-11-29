// https://www.geeksforgeeks.org/dsa/longest-subarray-sum-divisible-k/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    unordered_map<int, int> index;
    int maxLen = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = ((sum + arr[i]) % k + k) % k;
        if (sum == 0)
            maxLen = i + 1;
        else if (index.find(sum) != index.end())
        {
            maxLen = max(maxLen, i - index[sum]);
        }
        else
        {
            index[sum] = i;
        }
    }
    cout << maxLen;
}