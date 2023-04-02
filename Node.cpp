#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <sstream>

//
//  Node.h
//
//  Class for the data storage unit
//  of the Binary Seacrh Trees
//

namespace Project
{
class Node
{
   public:
    Node() {}
    Node(int x) : key(x), height(1), right(nullptr), left(nullptr) {}
    int key;
    Node* right;
    Node* left;
    int height;
    int updateAllHeights();
};

int Node::updateAllHeights()
{
    int l, r;
    if(this->left)
        l = this->left->updateAllHeights() + 1;
    else
        l = 1;

    if(this->right)
        r = this->right->updateAllHeights() + 1;
    else
        r = 1;

    int h = l > r ? l : r;
    this->height = h;
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

int toInt(std::string str)
{
    std::stringstream conversion;
    int res;
    conversion << str;
    conversion >> res;
    return res;
}

Node* minVal(Node* root)
{
    Node* cur = root;
    while(cur->left)  //
        cur = cur->left;

    return cur;
}
}  // namespace Project
#endif  // NODE_H
