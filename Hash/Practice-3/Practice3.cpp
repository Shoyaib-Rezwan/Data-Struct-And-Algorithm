#include <bits/stdc++.h>
using namespace std;
struct Node
{
    string name, NID, Phone;
};
int main()
{
    unordered_map<string, Node *> map1, map2, map3;
    while (true)
    {
        cout << "Enter choice: 1. Enter Data, 2. Search Index:\n";
        int cmd;
        fflush(stdin);
        cin >> cmd;
        if (cmd == 1)
        {
            Node *temp = new Node();
            cout << "Enter name: ";
            fflush(stdin);
            getline(cin, temp->name);
            cout << "Enter NID: ";
            fflush(stdin);
            cin >> temp->NID;
            cout << "Enter phone no.: ";
            fflush(stdin);
            cin >> temp->Phone;
            map1[temp->name] = temp;
            map2[temp->NID] = temp;
            map3[temp->Phone] = temp;
        }
        else
        {
            cout << "Enter search string: ";
            string str;
            fflush(stdin);
            getline(cin, str);
            Node *data = nullptr;
            if (map1.find(str) != map1.end())
            {
                data = map1[str];
            }
            else if (map2.find(str) != map2.end())
            {
                data = map2[str];
            }
            else if (map3.find(str) != map3.end())
            {
                data = map3[str];
            }
            if (data)
            {
                cout << "Match Found\n";
                cout << "Name: " << data->name << '\n';
                cout << "NID: " << data->NID << '\n';
                cout << "Phone no.: " << data->Phone << '\n';
            }
            else
            {
                cout << "No match found\n";
            }
        }
    }
}