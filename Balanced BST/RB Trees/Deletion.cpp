#include <bits/stdc++.h>
#include "./color.hpp"
using namespace std;
enum color
{
    RED,
    BLACK
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
    Node *NIL;

    void leftRotate(Node *x)
    {
        Node *temp = x->right;
        if (temp == NIL)
            return;
        x->right = temp->left;
        if (x->parent == nullptr)
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
        if (x->parent == nullptr)
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
    Node *BSTInsert(Node *root, Node *pt)
    {
        if (root == NIL)
            return pt;
        if (pt->data < root->data)
        {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else
        {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }
    void fixInsert(Node *pt)
    {
        Node *parent, *grandparent, *uncle;
        while (pt->parent != nullptr && pt->parent->color == RED && pt->color == RED)
        {
            parent = pt->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left)
            {
                uncle = grandparent->right;
                if (uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = uncle->color = BLACK;
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
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
            else
            {
                uncle = grandparent->left;
                if (uncle->color == RED)
                {
                    grandparent->color = RED;
                    uncle->color = parent->color = BLACK;
                    pt = grandparent;
                }
                else
                {
                    if (pt == parent->left)
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
    Node *searchNode(Node *root, int key)
    {
        if (root == NIL)
            return NIL;
        if (root->data == key)
            return root;
        if (key < root->data)
            return searchNode(root->left, key);
        return searchNode(root->right, key);
    }

    // transplant is the function that connects u's parent to v isolating u as a single node so that we can delete it afterwards
    void transplant(Node *u, Node *v)
    {
        // handle case when u is the root
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    // we will delete fix only if x is a double black and not a root
    void deleteFix(Node *x)
    {
        Node *w; // sibling
        // for checking that x is a root or not don't use x->parent!=nullptr because  is x is NIL then it will still have no parent
        while (x != root && x->color == BLACK)
        {
            // handle cases when x is the left child
            if (x == x->parent->left)
            {
                // catch the sibling
                w = x->parent->right;
                // when sibling is red, convert it to one of the cases where the sibling is black
                if (w->color == RED)
                {
                    // w is red so parent will be black. Swap their color and make a left rotation to balance the black count in both sides
                    swap(w->color, x->parent->color);
                    leftRotate(x->parent);
                    // replace w
                    w = x->parent->right;
                }
                ////now handle cases where w is black
                // after the above rotation, w is must black

                // if both children of w are black then we cannot use any of them to absorb the extra blackness of x, here we will precolate up the extra black, make w red and assign the extra black to parent
                if (w->left->color == BLACK && w->right->color == BLACK)
                {
                    w->color = RED;
                    x = x->parent;
                }
                else // atleast one of w's child is red
                {
                    // if only the nearest nephew of x is red
                    // send it to the farthest nephew position
                    if (w->right->color == BLACK)
                    {
                        w->color = RED;
                        w->left->color = BLACK;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // finally handle the case where the far nephew is red
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            // now mirroall the above cases where x is the right child
            else
            {
                w = x->parent->left;
                if (w->color == RED)
                {
                    swap(w->color, x->parent->color);
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
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RBTree()
    {
        NIL = new Node(0);
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL;
        root = NIL;
    }
    void insert(int key)
    {
        Node *pt = new Node(key);
        pt->left = pt->right = NIL;
        root = BSTInsert(root, pt);
        fixInsert(pt);
    }
    void print()
    {
        printHelper(root);
        cout << '\n';
    }
    void printHelper(Node *root)
    {
        if (root == NIL)
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
    void deleteNode(int key)
    {
        // z is the node to be deleted
        Node *z = searchNode(root, key);
        if (z == NIL)
            return;  // key is not found
        Node *x;     // x is the node that may need fixing after the deletion of z
        Node *y = z; // z is the parent of x. For now, set it equals to z;
        // keep track of y's original color
        bool y_original_color = z->color;

        // now handle cases similar to normal BST Node deletion
        // z's left child is NIL
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, x);
        }
        // z's right child is NIL
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, x);
        }
        // z has both children
        else
        {
            // find z's successor
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
            z->left->parent = y;
            z->right->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK)
            deleteFix(x);
    }
};
int main()
{
    RBTree tree;
    while (true)
    {
        int cmd, x;
        cin >> cmd >> x;
        if (cmd == 1)
        {
            cout << "Insert: " << x << '\n';
            tree.insert(x);
            tree.print();
        }
        if (cmd == 2)
        {
            {
                cout << "Insert: " << x << '\n';
                tree.deleteNode(x);
                tree.print();
            }
        }
    }
}