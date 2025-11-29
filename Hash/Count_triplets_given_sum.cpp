// https://www.geeksforgeeks.org/dsa/3-sum-count-all-triplets-with-given-sum/
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
    int k;
    cin >> k;
    unordered_map<int, int> pairFreq;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count += pairFreq[k - arr[i]];
        for (int j = 0; j < i; j++)
        {
            pairFreq[arr[i] + arr[j]]++;
        }
    }
    cout << count;
}