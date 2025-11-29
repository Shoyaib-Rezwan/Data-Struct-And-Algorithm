#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, sum;
    cin >> n >> sum;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    unordered_map<int, int> index;
    index[0] = -1; // to handle subarrays starting from 0
    int prefix_sum = 0, start = -1, end = -1;
    for (int i = 0; i < n; i++)
    {
        prefix_sum += arr[i];
        if (index.find(prefix_sum - sum) != index.end())
        {
            start = index[prefix_sum - sum] + 1;
            end = i;
            break;
        }
        if (index.find(prefix_sum) == index.end())
        {
            index[prefix_sum] = i;
        }
    }
    if (start == -1)
    {
        cout << "Subarray not found!!";
    }
    else
    {
        cout << start << ' ' << end;
    }
}