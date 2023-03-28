#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "Node.h"

using namespace std;

extern bool debugger;
extern bool debugger1;

class AVLTree
{
   private:
    Node* _root;

   public:
    AVLTree() : _root(nullptr) {}
    ~AVLTree();

    // deletes all the nodes of a tree
    void clear(Node* root);

    // adds a node with value 'key' to the tree
    void insert(int key) { _root = insert(_root, key); }

    // deletes the node with value 'key' from the tree
    void remove(int key) { _root = remove(_root, key); }

    // returns the balance factor of a given node
    int static balanceFactor(Node* cur);

    // safely returns the root of the tree
    Node* returnRoot() { return _root; }

    // does a right rotation of a given node
    Node* rightRotate(Node* y);

    // does a left rotation of a given node
    Node* leftRotate(Node* x);

    Node* insert(Node* node, int key)
    {
        // base case: root OR place a new node
        if(node == nullptr)
            return new Node(key);

        // traverse left/right to place the node
        if(key < node->key)
            node->left = insert(node->left, key);

        else if(key > node->key)
            node->right = insert(node->right, key);

        else
            return node;

        // update Heights
        node->height = 1 + maxHeight(node->left, node->right);
        if(debugger)
            cout << "curernt" << endl;
        int test = updateAllHeights(_root);
        //        if(debugger)
        //            print(_root);

        // check balances
        int bf = balanceFactor(node);
        if(debugger)
            if(node)
                cout << "BF =  " << bf << '\t' << " NODE " << node->key << '\t' << key << endl;

        // rotate the tree if needed
        if(bf > 1 || bf < -1)
        {
            if(debugger)
                cout << "choosing case" << endl;

            if(bf > 1 && key < node->left->key)
            {
                if(debugger)
                    cout << "========CASE1=========" << endl;
                return rightRotate(node);
            }

            if(bf > 1 && key > node->left->key)
            {
                if(debugger)
                    cout << "========CASE2=========" << endl;
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if(bf < -1 && key > node->right->key)
            {
                if(debugger)
                    cout << "========CASE3=========" << endl;
                return leftRotate(node);
            }

            if(bf < -1 && key < node->right->key)
            {
                if(debugger)
                    cout << "========CASE4=========" << endl;
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    Node* remove(Node* node, int key)
    {
        cout << "";
        // base Case: root OR place a new node
        if(node == nullptr)
            return node;

        // traverse left/right to place the node
        if(key < node->key)
            node->left = remove(node->left, key);

        else if(key > node->key)
            node->right = remove(node->right, key);

        // suitable place was found
        else
        {
            if(!node->left || !node->right)
            {
                Node* temp = nullptr;
                if(node->left)
                    temp = node->left;
                else if(node->right)
                    temp = node->right;

                if(!temp)
                {
                    // cout << "I AM HERE " << node->key << endl;
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                free(temp);  // check if its needed
            }
            else
            {
                Node* temp = minVal(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }

        if(node == nullptr)
            return node;

        // update Heights
        node->height = 1 + maxHeight(node->left, node->right);
        if(debugger1)
            cout << "curernt" << endl;
        int test = updateAllHeights(_root);
        //        if(debugger1)
        //            print(node);

        // check balances
        int bf = balanceFactor(node);
        if(debugger1)
            if(node)
                cout << "BF =  " << bf << '\t' << " NODE " << node->key << '\t' << key << endl;

        // rotate the tree if needed
        if(bf > 1 || bf < -1)
        {
            if(debugger1)
                cout << "choosing case" << endl;

            if(bf > 1 && balanceFactor(node->left) >= 0)
            {
                if(debugger1)
                    cout << "========CASE1=========" << endl;
                return rightRotate(node);
            }

            if(bf > 1 && balanceFactor(node->left) < 0)
            {
                if(debugger1)
                    cout << "========CASE2=========" << endl;
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }

            if(bf < -1 && balanceFactor(node->right) <= 0)
            {
                if(debugger1)
                    cout << "========CASE3=========" << endl;
                return leftRotate(node);
            }

            if(bf < -1 && balanceFactor(node->right) > 0)
            {
                if(debugger1)
                    cout << "========CASE4=========" << endl;
                node->right = rightRotate(node->right);

                return leftRotate(node);
            }
        }

        return node;
    }
};

Node* AVLTree::rightRotate(Node* y)
{
    // definitions
    Node* x = y->left;
    Node* t2 = x->right;

    // rotations
    x->right = y;
    y->left = t2;

    // updates
    y->height = 1 + maxHeight(y->left, y->right);
    x->height = 1 + maxHeight(x->left, x->right);

    return x;
}

Node* AVLTree::leftRotate(Node* x)
{
    // definitions
    Node* y = x->right;
    Node* t2 = y->left;

    // rotations
    y->left = x;
    x->right = t2;

    // updates
    y->height = 1 + maxHeight(y->left, y->right);
    x->height = 1 + maxHeight(x->left, x->right);

    return y;
}

int AVLTree::balanceFactor(Node* cur)
{
    // if the node is root return 0
    if(cur == nullptr)
        return 0;

    // get the heigths of left and right subtrees
    int l, r;
    if(cur->left == nullptr)
        l = 0;
    else
        l = cur->left->height;

    if(cur->right == nullptr)
        r = 0;
    else
        r = cur->right->height;

    // return the difference
    return l - r;
}

AVLTree::~AVLTree() { clear(_root); }

void AVLTree::clear(Node* root)
{
    if(root)
    {
        clear(root->left);
        clear(root->right);
        delete root;
    }
}

#endif  // AVLTREE_H
