#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<string> from(n), to(n);
    unordered_map<string, string> ford, rev;
    for (int i = 0; i < n; i++)
    {
        string str, a, b;
        fflush(stdin);
        getline(cin, str);
        int arrowPos = str.find("->");
        a = str.substr(0, arrowPos - 1);
        b = str.substr(arrowPos + 3);
        from[i] = a.substr(1, a.length() - 2);
        to[i] = b.substr(1, b.length() - 2);
        ford[from[i]] = to[i];
        rev[to[i]] = from[i];
    }
    // find the initial city
    string init = "";
    for (int i = 0; i < n; i++)
    {
        if (rev.find(from[i]) == rev.end())
        {
            init = from[i];
            break;
        }
    }
    cout << init << ' ';
    while (ford.find(ford[init]) != ford.end())
    {
        cout << ford[init] << ' ';
        init = ford[init];
    }
    cout << ford[init];
}