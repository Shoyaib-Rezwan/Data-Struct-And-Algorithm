#include <iostream>
#include <fstream>
using namespace std;
enum
{
    RED,
    BLACK
};
class Node
{
public:
    string key;
    int value;
    bool color;
    Node *left, *right, *parent;
    Node(string key, int value)
    {
        this->key = key;
        this->value = value;
    }
};
class RedBlackTree
{
    Node *root, *NIL;
    int count;
    Node *insertHelper(Node *root, Node *pt, int &count)
    {
        if (root == NIL)
            return pt;
        if (pt->key < root->key)
        {
            count++;
            root->left = insertHelper(root->left, pt, count);
            root->left->parent = root;
        }
        else if (pt->key > root->key)
        {
            count++;
            root->right = insertHelper(root->right, pt, count);
            root->right->parent = root;
        }
        return root;
    }
    void leftRotate(Node *x)
    {
        Node *temp = x->right;
        if (temp == NIL)
            return;
        x->right = temp->left;
        if (x == root)
            root = temp;
        else if (x == x->parent->left)
            x->parent->left = temp;
        else
            x->parent->right = temp;
        if (temp->left != NIL)
            temp->left->parent = x;
        temp->parent = x->parent;
        x->parent = temp;
        temp->left = x;
    }
    void rightRotate(Node *x)
    {
        Node *temp = x->left;
        if (temp == NIL)
            return;
        x->left = temp->right;
        if (x == root)
            root = temp;
        else if (x == x->parent->left)
            x->parent->left = temp;
        else
            x->parent->right = temp;
        if (temp->right != NIL)
            temp->right->parent = x;
        temp->parent = x->parent;
        x->parent = temp;
        temp->right = x;
    }

    void insertFix(Node *pt)
    {
        while (pt != root && pt->parent->color == RED && pt->color == RED)
        {
            Node *parent = pt->parent;
            Node *grandparent = parent->parent;
            // when parent is the left child
            if (parent == grandparent->left)
            {
                Node *uncle = grandparent->right;
                if (uncle->color == RED)
                {
                    parent->color = uncle->color = BLACK;
                    grandparent->color = RED;
                    pt = grandparent;
                }
                else
                {
                    if (pt == parent->right)
                    {
                        leftRotate(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    rightRotate(grandparent);
                    swap(grandparent->color, parent->color);
                    pt = parent;
                }
            }
            // when parent is the right child
            else
            {
                Node *uncle = grandparent->left;
                if (uncle->color == RED)
                {
                    parent->color = uncle->color = BLACK;
                    grandparent->color = RED;
                    pt = grandparent;
                }
                else
                {
                    if (parent->left == pt)
                    {
                        rightRotate(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    leftRotate(grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
        }
        root->color = BLACK;
    }
    void clearHelper(Node *root)
    {
        if (root == NIL)
            return;
        clearHelper(root->left);
        clearHelper(root->right);
        delete root;
    }

    void transplant(Node *u, Node *v)
    {
        if (u == root)
            root = v;
        else if (u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    void deleteFix(Node *x)
    {
        while (x != root && x->color == BLACK)
        {
            Node *w;
            if (x->parent->left == x)
            {
                w = x->parent->right;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == BLACK)
                    {
                        w->color = RED;
                        w->left->color = BLACK;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                w = x->parent->left;
                if (w->color == RED)
                {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == BLACK)
                    {
                        w->color = RED;
                        w->right->color = BLACK;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->left->color = BLACK;
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }
    Node *searchHelper(Node *root, string key)
    {
        if (root == NIL)
            return NIL;
        if (root->key == key)
            return root;
        if (key < root->key)
            return searchHelper(root->left, key);
        return searchHelper(root->right, key);
    }

public:
    RedBlackTree()
    {
        NIL = new Node("", 0);
        NIL->left = NIL->right = NIL;
        NIL->color = BLACK;
        root = NIL;
        count = 0;
    }
    int insert(string key, int value)
    {
        Node *pt = new Node(key, value);
        pt->left = pt->right = NIL;
        bool newInsert = true;
        int count = 0;
        root = insertHelper(root, pt, count);
        if (newInsert)
        {
            insertFix(pt);
            count++;
        }
        return count;
    }
    string clear()
    {
        if (root == NIL)
            return "unsuccessful";
        clearHelper(root);
        root = NIL;
        count = 0;
        return "successful";
    }
    bool isEmpty()
    {
        return count == 0;
    }
    int size()
    {
        return count;
    }
    void deleteNode(string key)
    {
        Node *z = searchHelper(root, key);
        if (z == NIL)
            return;
        Node *y = z;
        Node *x;
        bool y_original_color = z->color;
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, x);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, x);
        }
        else
        {
            y = z->right;
            while (y->left != NIL)
            {
                y = y->left;
            }
            y_original_color = y->color;
            x = y->right;
            transplant(y, x);
            transplant(z, y);
            y->left = z->left;
            y->right = z->right;
            y->left->parent = y->right->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK)
        {
            deleteFix(x);
        }
        count--;
    }
    Node *end()
    {
        return NIL;
    }
    Node *search(string key)
    {
        return searchHelper(root, key);
    }
    pair<string, int> getRoot()
    {
        if (root == NIL)
            return {"", -1};
        return {root->key, root->value};
    }
};