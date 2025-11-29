#include <bits/stdc++.h>
using namespace std;
string getReverseComplement(const string &str)
{
    string complement;
    for (char x : str)
    {
        switch (x)
        {
        case 'A':
            complement += "T";
            break;
        case 'T':
            complement += "A";
            break;
        case 'C':
            complement += "G";
            break;
        case 'G':
            complement += "C";
            break;
        }
    }
    reverse(complement.begin(), complement.end());
    return complement;
}
int main()
{
    int n, l;
    cin >> n >> l;
    vector<string> sequences(n);
    unordered_map<string, int> freq;
    for (int i = 0; i < n; i++)
    {
        cin >> sequences[i];
        freq[sequences[i]]++;
    }
    unordered_map<string, bool> processed;
    for (const string &str : sequences)
    {
        if (!processed[str])
        {
            string rev = getReverseComplement(str);
            if (rev == str)
            {
                int count = (freq[str] * (freq[str] - 1)) / 2;
                for (int i = 0; i < count; i++)
                {
                    cout << str << ' ' << rev << '\n';
                }
            }
            else
            {
                int count = freq[str] * freq[rev];
                for (int i = 0; i < count; i++)
                {
                    cout << str << ' ' << rev << '\n';
                }
            }
            processed[str] = true;
            processed[rev] = true;
        }
    }
}