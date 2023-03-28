#ifndef NODE_H
#define NODE_H

//
//  Node.h
//
//  Class for the data storage unit
//  of the Binary Seacrh Trees

class Node
{
   public:
    Node() {}
    Node(int x) : key(x), height(1), right(nullptr), left(nullptr) {}
    int key;
    int height;
    Node* right;
    Node* left;

    int updateAllHeights(Node* root);
    int maxHeight(Node* left, Node* right);
    Node* minVal(Node* root);
};

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

Node* minVal(Node* root)
{
    Node* cur = root;
    while(cur->left)  //
        cur = cur->left;

    return cur;
}

#endif  // NODE_H
