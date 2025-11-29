#include <bits/stdc++.h>
#include "./color.hpp"
using namespace std;
enum color
{
    RED,  // 0
    BLACK // 1
};
struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;
    Node(int data) : data(data)
    {
        color = RED;
        left = right = parent = nullptr;
    }
};
class RBTree
{
    Node *root;

public:
    RBTree()
    {
        root = nullptr;
    }
    void leftRotate(Node *x)
    {
        Node *temp = x->right;
        if (!temp)
            return;
        x->right = temp->left;
        if (x->parent == nullptr)
            root = temp;
        else if (x->parent->left == x)
            x->parent->left = temp;
        else
            x->parent->right = temp;
        if (temp->left)
            temp->left->parent = x;
        temp->parent = x->parent;
        x->parent = temp;
        temp->left = x;
    }
    void rightRotate(Node *x)
    {
        Node *temp = x->left;
        if (!temp)
            return;
        x->left = temp->right;
        if (!x->parent)
            root = temp;
        else if (x->parent->left == x)
            x->parent->left = temp;
        else
            x->parent->right = temp;
        temp->parent = x->parent;
        x->parent = temp;
        if (temp->right)
            temp->right->parent = x;
        temp->right = x;
    }

    Node *bstInsert(Node *root, Node *pt)
    {
        if (!root)
            return pt;
        if (pt->data < root->data)
        {
            root->left = bstInsert(root->left, pt);
            root->left->parent = root;
        }
        else
        {
            root->right = bstInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    void fixInsert(Node *&pt)
    {
        Node *parent = nullptr, *grandparent = nullptr;
        // continue fixing all the red-red conflict cases except the root - red case
        while (pt != root && pt->color == RED and pt->parent->color == RED)
        {
            parent = pt->parent;
            grandparent = parent->parent;

            // parent is the left child of grandparent
            if (parent == grandparent->left) // notice grandparent will never become null cause both child and parent are red so the grand parent has to be a black node as we arer inserting the child into a valid RB tree
            {
                Node *uncle = grandparent->right;
                // case: uncle is red
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    uncle->color = parent->color = BLACK;
                    pt = grandparent;
                }
                // case: uncle is black

                // triangle case
                if (parent->right == pt)
                {
                    leftRotate(parent);
                    pt = parent;
                    parent = pt->parent;
                }
                // line case
                rightRotate(grandparent);
                swap(grandparent->color, parent->color);
                // catch it: after this case is handled, all RB properties are restored
                pt = parent; // pt is black
            }
            // parent is the right child of grandparent
            // mirror cases of the above mentioned case
            if (parent == grandparent->right)
            {
                Node *uncle = grandparent->left;
                // case: uncle is red
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    uncle->color = parent->color = BLACK;
                    pt = grandparent;
                }
                // uncle is black(even if it's null-> it will be black)
                else
                {
                    // triangle case
                    if (parent->left == pt)
                    {
                        rightRotate(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // line case
                    leftRotate(grandparent);
                    swap(grandparent->color, parent->color);
                    pt = parent;
                }
            }
        }
        root->color = BLACK;
    }

public:
    void insert(int data)
    {
        Node *pt = new Node(data);
        root = bstInsert(root, pt);
        fixInsert(pt);
    }
    void print()
    {
        printHelper(root);
        cout << '\n';
    }
    void printHelper(Node *root)
    {
        if (!root)
            return;
        if (root->color == RED)
            cout << dye::red(root->data);
        else
            cout << root->data;
        cout << "( ";
        printHelper(root->left);
        cout << " , ";
        printHelper(root->right);
        cout << " )";
    }
};
int main()
{
    RBTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(5);
    tree.insert(11);
    tree.print();
}