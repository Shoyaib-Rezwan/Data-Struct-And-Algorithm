#include <bits/stdc++.h>
#include "RB_Tree.hpp"
using namespace std;
using namespace std::chrono;
void generateWords(int n, vector<string> &words)
{
    ofstream ofs("words.txt");
    srand(time(NULL));
    int len, ch;
    string str;
    for (int i = 0; i < n; i++)
    {
        len = 5 + rand() % 6;
        str = "";
        for (int j = 0; j < len; j++)
        {
            str += ('a' + rand() % 26);
        }
        ofs << str << '\n';
        words.push_back(str);
    }
    ofs.close();
}
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
} // polynomial rolling hash 31 based hashing
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
class ChainedHashTable
{
    vector<RedBlackTree> table;
    int collisionCount;
    int m;
    unsigned long long (*hashf)(const string, int);

public:
    ChainedHashTable(int m, unsigned long long (*hashf)(const string, int))
    {
        this->m = m;
        table.resize(m);
        collisionCount = 0;
        this->hashf = hashf;
    }
    bool insert(string key, int value)
    {
        int index = hashf(key, m);
        if (table[index].search(key) != table[index].end())
        {
            // duplicate
            return false;
        }
        else if (!table[index].isEmpty())
        {
            // collision occurrs
            collisionCount++;
        }
        collisionCount += table[index].insert(key, value);
        return true;
    }
    int getCollisionCount()
    {
        return collisionCount;
    }
    int search(string key)
    {
        int index = hashf(key, m);
        auto x = table[index].search(key);
        if (x == table[index].end())
            return -1;
        else
            return x->value;
    }
    void deleteKey(string key)
    {
        int index = hashf(key, m);
        table[index].deleteNode(key);
    }
    int maxChainLen()
    {
        int maxLen = 0;
        for (auto x : table)
        {
            maxLen = max(maxLen, x.size());
        }
        return maxLen;
    }
    void reHash(int m)
    {
        this->m = m;
        vector<RedBlackTree> oldTable = table;
        table.clear();
        table.resize(m);
        for (int i = 0; i < oldTable.size(); i++)
        {
            while (oldTable[i].size() > 0)
            {
                insert(oldTable[i].getRoot().first, oldTable[i].getRoot().second);
                oldTable[i].deleteNode(oldTable[i].getRoot().first);
            }
        }
        oldTable.clear();
    }
};
void displayTimeProbes(ChainedHashTable &chainedHashTable, vector<string> &searchSet)
{
    double totalTimeChain1 = 0, totalTimeChain2 = 0, totalTimeLinear1 = 0, totalTimeLinear2 = 0, totalProbeLinear1 = 0, totalProbeLinear2 = 0, totalTimeDouble = 0, totalProbeDouble = 0;
    for (string key : searchSet)
    {
        // chained hash 1
        auto start = high_resolution_clock::now();
        chainedHashTable.search(key);
        auto end = high_resolution_clock::now();
        totalTimeChain1 += duration<double, micro>(end - start).count();
    }
    cout << "Average time for seacrh in chained method with hash 1: " << totalTimeChain1 / (1.0 * searchSet.size()) << " micro second\n";
    cout << "Average number of probes with hash 1: " << chainedHashTable.getCollisionCount() / (1.0 * searchSet.size()) << "\n";
}
vector<string> tenPercentRandom(vector<string> &arr)
{
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);
    return vector<string>(arr.begin(), arr.begin() + arr.size() / 10);
}

int main()
{
    int N;
    cin >> N;
    int m = nextPrime(N);
    int c;
    cin >> c;
    ChainedHashTable table(m, hash1);
    vector<string> words;
    generateWords(10000, words);
    for (int i = 0; i < 10000; i += 100)
    {
        for (int j = 0; j < 100; j++)
        {
            table.insert(words[i + j], i + j);
        }
        if (table.maxChainLen() >= c)
            break;
    }
    vector<string> temp = tenPercentRandom(words);
    displayTimeProbes(table, temp);
    m = nextPrime(m * 2);
    table.reHash(m);
    temp = tenPercentRandom(words);
    displayTimeProbes(table, temp);
}