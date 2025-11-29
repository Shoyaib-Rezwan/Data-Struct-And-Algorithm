#include <bits/stdc++.h>
using namespace std;
int nextPrime(int num)
{
    bool isPrime = true;
    for (int i = num + 1;; i++)
    {
        if (i <= 1)
            continue;
        isPrime = true;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            return i;
    }
    return -1;
}
// polynomial rolling hash 31 based hashing
unsigned long long hash1(const string key, int m)
{
    unsigned long long hash = 0;
    for (char x : key)
    {
        hash = (hash * 31 + x) % m;
    }
    return hash;
}
// DJB2 Hashing-> 33 based hashing
unsigned long long hash2(const string key, int m)
{
    unsigned long long hash = 5381;
    for (char x : key)
    {
        hash = ((hash << 5) + hash + x) % m; // same as before just base is 33
    }
    return (hash == 0) ? 1 : hash;
}
class HashTable2
{
    vector<pair<string, int>> table;
    int m;
    int collisionCount;

public:
    HashTable2(int m)
    {
        this->m = m;
        collisionCount = 0;
        table.resize(m, {"", -1});
    }
    bool insert(string key, int value)
    {
        int init = hash1(key, m); // initial probe number
        int s = hash2(key, m);
        int index;
        // bool collision = false;
        for (int i = 0; i < m; i++)
        {
            index = (init + i * s) % m;
            if (table[index].first == key)
                return false; // duplicate
            else if (table[index].first == "" || table[index].first == "DELETED")
            {
                table[index] = {key, value};
                return true;
            }
            // else if (!collision)
            // {
            collisionCount++;
            // collision = true;
            // }
        }
        return false;
    }
    int getCollisionCount() { return collisionCount; }
    pair<int, int> search(string key)
    {
        int init = hash1(key, m);
        int s = hash2(key, m), index;
        for (int i = 0; i < m; i++)
        {
            index = (init + i * s) % m;
            if (table[index].first == "")
                return {-1, i + 1};
            else if (table[index].first == key)
                return {table[index].second, i + 1};
        }
        return {-1, m};
    }
    void deleteKey(string key)
    {
        int init = hash1(key, m);
        int s = hash2(key, m), index;
        for (int i = 0; i < m; i++)
        {
            index = (init + i * s) % m;
            if (table[index].first == "")
                return;
            if (table[index].first == key)
            {
                table[index].first = "DELETED";
                table[index].second = -1;
                return;
            }
        }
    }
    vector<pair<string, int>> getAll()
    {
        vector<pair<string, int>> result;
        for (auto x : table)
        {
            if (x.first != "")
                result.push_back(x);
        }
        return result;
    }
};
class HashTable1
{
    vector<pair<string, HashTable2 *>> table;
    int m;
    int collisionCount;

public:
    HashTable1(int m)
    {
        this->m = m;
        collisionCount = 0;
        table.resize(m, {"", nullptr});
    }
    bool insert(string key1, string key2, int value)
    {
        int init = hash1(key1, m); // initial probe number
        int s = hash2(key1, m);
        int index;
        // bool collision = false;
        for (int i = 0; i < m; i++)
        {
            index = (init + i * s) % m;
            if (table[index].first == key1)
                table[index].second->insert(key2, value);
            else if (table[index].first == "" || table[index].first == "DELETED")
            {
                table[index] = {key1, new HashTable2(m)};
                table[index].second->insert(key2, value);
                return true;
            }
            // else if (!collision)
            // {
            collisionCount++;
            // collision = true;
            // }
        }
        return false;
    }
    int getCollisionCount() { return collisionCount; }
    // pair<int, int> search(string key)
    // {
    //     int init = hash1(key, m);
    //     int s = hash2(key, m), index;
    //     for (int i = 0; i < m; i++)
    //     {
    //         index = (init + i * s) % m;
    //         if (table[index].first == "")
    //             return {-1, i + 1};
    //         else if (table[index].first == key)
    //             return {table[index].second, i + 1};
    //     }
    //     return {-1, m};
    // }
    string find(string key1, string key2)
    {
        int init = hash1(key1, m);
        int s = hash2(key1, m), index;
        for (int i = 0; i < m; i++)
        {
            index = (init + s * i) % m;
            if (table[index].first == key1 && table[index].second->search(key2).first != -1)
            {
                return to_string(table[index].second->search(key2).first);
            }
        }
        return "";
    }
    vector<pair<string, int>> find(string key1)
    {
        int init = hash1(key1, m);
        int s = hash2(key1, m), index;
        for (int i = 0; i < m; i++)
        {
            index = (init + s * i) % m;
            if (table[index].first == key1)
            {
                return table[index].second->getAll();
            }
        }
        return {};
    }
    void deleteKey(string key)
    {
        int init = hash1(key, m);
        int s = hash2(key, m), index;
        for (int i = 0; i < m; i++)
        {
            index = (init + i * s) % m;
            if (table[index].first == "")
                return;
            if (table[index].first == key)
            {
                table[index].first = "DELETED";
                table[index].second = nullptr;
                return;
            }
        }
    }
};

int main()
{
    int n = 100;
    n = nextPrime(n);
    HashTable1 table(n);
    table.insert("bd", " dhaka", 500);
    table.insert("bd", " ctg", 300);
    table.insert("uk", " london", 800);

    cout << table.find("bd", " dhaka");
    cout << table.find("bd", " syl");
    vector<pair<string, int>> result = table.find("bd");
    for (auto x : result)
    {
        cout << x.first << ' ' << x.second << '\n';
    }
    result = table.find("china");
    for (auto x : result)
    {
        cout << x.first << ' ' << x.second << '\n';
    }
}