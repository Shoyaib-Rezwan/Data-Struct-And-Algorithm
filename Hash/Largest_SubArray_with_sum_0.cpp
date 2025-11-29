// https://www.geeksforgeeks.org/dsa/find-subarray-with-given-sum-in-array-of-integers/
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i < n; i++)
    {
        arr[i] = arr[i - 1] + arr[i];
    }
    int maxlen = 0;
    unordered_map<int, int> ind;
    for (int i = 0; i < n; i++)
    {
        if (ind.find(arr[i]) == ind.end())
        {
            ind[arr[i]] = i;
        }
        else
        {
            maxlen = max(maxlen, i - ind[arr[i]]);
        }
    }
    cout << maxlen << '\n';
}