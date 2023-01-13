#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

extern bool debugger;
extern bool debugger1;

class AVLTree
{
   public:
    class Node
    {
       public:
        Node() {}
        Node(int x) : key(x), height(1), right(nullptr), left(nullptr) {}
        int key;
        int height;
        Node* right;
        Node* left;
    };

    AVLTree() : _root(nullptr) {}
    ~AVLTree();
    Node* _root;
    void clear(Node* root);
    void print(Node* root, bool ch = false);

    void insert(int key) { _root = insert(_root, key); }

    Node* insert(Node* node, int key)
    {
        if(node == nullptr)
            return new Node(key);

        // Traverse left/right
        if(key < node->key)
            node->left = insert(node->left, key);

        else if(key > node->key)
            node->right = insert(node->right, key);

        else
            return node;

        // STEP 2
        // Update Heights
        node->height = 1 + maxHeight(node->left, node->right);
        if(debugger)
            cout << "curernt" << endl;
        int test = updateAllHeights(_root);
        if(debugger)
            print(_root);

        // STEP 3
        // Check Balances
        int bf = balanceFactor(node);
        if(debugger)
            if(node)
                cout << "BF =  " << bf << '\t' << " NODE " << node->key << '\t' << key << endl;

        // STEP 4
        // ROTATE if needed
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

    int updateAllHeights(Node* root)
    {
        int l, r;
        if(root->left)
            l = updateAllHeights(root->left) + 1;

        else
            l = 1;

        if(root->right)
            r = updateAllHeights(root->right) + 1;

        else
            r = 1;

        int h = l > r ? l : r;
        root->height = h;
        return h;
    }

    Node* rightRotate(Node* y)
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

    Node* leftRotate(Node* x)
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

    int maxHeight(Node* left, Node* right)
    {
        // get heights of left and right subtrees
        int l, r;
        if(left == nullptr)
            l = 0;
        else
            l = left->height;

        if(right == nullptr)
            r = 0;
        else
            r = right->height;

        // return the max height
        return l >= r ? l : r;
    }

    int balanceFactor(Node* cur)
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

    void remove(int key) { _root = remove(_root, key); }

    Node* minVal(Node* root)
    {
        Node* cur = root;
        while(cur->left) cur = cur->left;

        return cur;
    }

    Node* remove(Node* node, int key)
    {
        cout << "";

        if(node == nullptr)
            return node;

        // Traverse left/right
        if(key < node->key)
            node->left = remove(node->left, key);

        else if(key > node->key)
            node->right = remove(node->right, key);

        else
        {
            if(!node->left || !node->right)
            {
                Node* temp;
                if(node->left)
                    temp = node->left;
                else if(node->right)
                    temp = node->right;

                if(!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                // free(temp);
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

        // STEP 2
        // Update Heights
        node->height = 1 + maxHeight(node->left, node->right);
        if(debugger1)
            cout << "curernt" << endl;
        int test = updateAllHeights(_root);
        if(debugger1)
            print(node);

        // STEP 3
        // Check Balances
        int bf = balanceFactor(node);
        if(debugger1)
            if(node)
                cout << "BF =  " << bf << '\t' << " NODE " << node->key << '\t' << key << endl;

        // STEP 4
        // ROTATE if needed
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

void AVLTree::print(Node* root, bool ch)
{
    if(ch == false)
    {
        cout << "Key" << '\t' << "L" << '\t' << "R" << '\t' << "BF" << '\t' << "H" << endl;
        ch = true;
    }

    cout << root->key << '\t';
    if(root->left)
        cout << root->left->key;
    cout << '\t';
    if(root->right)
        cout << root->right->key;
    cout << '\t';
    cout << balanceFactor(root);
    cout << '\t';
    cout << root->height << endl;

    if(root->left)
        AVLTree::print(root->left, ch);
    if(root->right)
        AVLTree::print(root->right, ch);
}

#endif  // AVLTREE_H
