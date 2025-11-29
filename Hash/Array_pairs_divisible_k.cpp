// https://www.geeksforgeeks.org/dsa/check-if-an-array-can-be-divided-into-pairs-whose-sum-is-divisible-by-k/
#include <bits/stdc++.h>
using namespace std;
bool canPair(vector<int> &arr, int k)
{
    if (arr.size() % 2)
        return false;
    unordered_map<int, int> freq;
    for (int i = 0; i < arr.size(); i++)
    {
        freq[(arr[i] % k + k) % k]++;
    }
    for (int x : arr)
    {
        int rem = (x % k + k) % k;
        if (rem == 0 && freq[rem] % 2)
        {
            return false;
        }
        else if (rem * 2 == k && freq[rem] % 2)
        {
            return false;
        }
        else if (freq[rem] != freq[k - rem])
            return false;
    }
    return true;
}
int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << canPair(arr, k);
}