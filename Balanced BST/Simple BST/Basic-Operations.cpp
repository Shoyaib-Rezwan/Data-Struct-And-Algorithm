#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int data;
    Node *left, *right;
    Node(int data) : data(data)
    {
        left = nullptr;
        right = nullptr;
    }
};
Node *insert(Node *root, int x)
{
    if (!root)
        return new Node(x);
    if (root->data > x)
    {
        root->left = insert(root->left, x);
    }
    else
    {
        root->right = insert(root->right, x);
    }
    return root;
}
bool search(Node *root, int x)
{
    if (!root)
        return false;
    if (root->data == x)
        return true;
    if (x < root->data)
        return search(root->left, x);
    return search(root->right, x);
}
Node *removeNode(Node *root, int x)
{
    if (!root)
        return nullptr;
    if (x < root->data)
        root->left = removeNode(root->left, x);
    else if (x > root->data)
        root->right = removeNode(root->right, x);
    else
    {
        if (!root->left)
        {
            Node *temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right)
        {
            Node *temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            Node *temp = root->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            swap(root->data, temp->data);
            root->right = removeNode(root->right, x);
        }
    }
    return root;
}
void print(Node *root)
{
    if (!root)
        return;
    cout << root->data;
    if (!root->left && !root->right)
        return;
    cout << "( ";
    print(root->left);
    cout << ",";
    print(root->right);
    cout << " )";
}
Node *leftRotate(Node *root, int x)
{
    if (!root)
        return nullptr;
    if (x < root->data)
        root->left = leftRotate(root->left, x);
    else if (x > root->data)
        root->right = leftRotate(root->right, x);
    else
    {
        if (!root->right)
            return root;
        Node *temp = root;
        root = root->right;
        temp->right = root->left;
        root->left = temp;
    }
    return root;
}
Node *rightRotate(Node *root, int x)
{
    if (!root)
        return nullptr;
    if (x < root->data)
        root->left = rightRotate(root->left, x);
    else if (x > root->data)
        root->right = rightRotate(root->right, x);
    else
    {
        if (!root->left)
            return root;
        Node *temp = root;
        root = root->left;
        temp->left = root->right;
        root->right = temp;
    }
    return root;
}
int main()
{
    Node *root = nullptr;
    while (true)
    {
        int cmd, x;
        cin >> cmd >> x;
        if (cmd == 4)
        {
            cout << "Program Exited...";
            break;
        }
        if (cmd == 1)
        {
            cout << "insert " << x << "\n";
            root = insert(root, x);
            print(root);
            cout << '\n';
        }
        if (cmd == 2)
        {
            cout << "serch " << x << "\n";
            bool result = search(root, x);
            // cout << result;
            if (result == true)
                cout << "Found\n";
            else
                cout << "Not Found\n";
        }
        if (cmd == 3)
        {
            cout << "delete " << x << "\n";
            root = removeNode(root, x);
            print(root);
            cout << '\n';
        }
        if (cmd == 5)
        {
            cout << "left-rotate " << x << "\n";
            root = leftRotate(root, x);
            print(root);
            cout << '\n';
        }
        if (cmd == 6)
        {
            cout << "right-rotate " << x << "\n";
            root = rightRotate(root, x);
            print(root);
            cout << '\n';
        }
    }
}