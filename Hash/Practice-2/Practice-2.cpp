#include <bits/stdc++.h>
using namespace std;
int main()
{
    int l, k;
    cin >> l >> k;
    string seq;
    cin >> seq;
    unordered_map<string, int> freq;
    for (int i = 0; i < l; i++)
    {
        string temp;
        for (int j = 0; j < 3; j++)
        {
            temp += seq[(i + j) % l];
        }
        freq[temp]++;
    }
    for (auto x : freq)
    {
        cout << x.first << ' ' << x.second << '\n';
    }
}