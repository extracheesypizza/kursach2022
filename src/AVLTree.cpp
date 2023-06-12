#include "AVLTree.hpp"

namespace Project
{
AVLTree::~AVLTree() { clear(root_); }

void AVLTree::insert(int key)
{
    root_ = insert(root_, key);
    root_->updateAllHeights();
    notify();
}

void AVLTree::remove(int key)
{
    root_ = remove(root_, key);
    if(root_)
        root_->updateAllHeights();
    notify();
}

Node* AVLTree::insert(Node* node, int key)
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

    return balanceIfNeeded(node);
}

Node* AVLTree::remove(Node* node, int key)
{
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
                temp = node;
                node = nullptr;
            }
            else
                *node = *temp;

            free(temp);
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

    return balanceIfNeeded(node);
}

Node* AVLTree::balanceIfNeeded(Node* node)
{
    // check balances
    root_->updateAllHeights();
    int bf = balanceFactor(node);

    // rotate the tree if needed
    if(bf > 1 || bf < -1)
    {
        if(bf > 1 && balanceFactor(node->left) >= 0)
            return rightRotate(node);

        else if(bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        else if(bf < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);

        else if(bf < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
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

int AVLTree::balanceFactor(Node* cur) const
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

int AVLTree::maxHeight(Node* left, Node* right)
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

Node* AVLTree::minVal(Node* root)
{
    Node* cur = root;
    while(cur->left)  //
        cur = cur->left;

    return cur;
}

// Many people online suggest it's an okay way of deallocating memory
void AVLTree::clear(Node* root)
{
    if(root)
    {
        Node* left = root->left;
        Node* right = root->right;
        delete root;

        clear(left);
        clear(right);
    }
}

void AVLTree::notify() { out_.notify(); }

}  // namespace Project
