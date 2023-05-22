#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <sstream>

#include "Node.hpp"

namespace Project
{
static bool isNumeric(std::string str)
{
    for(int i = 0; i < str.length(); i++)
        if(!isdigit(str[i]))
            return false;
    return true;
}

static int toInt(std::string str)
{
    std::stringstream conversion;
    int res;
    conversion << str;
    conversion >> res;
    return res;
}

static int maxHeight(Node* left, Node* right)
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

static Node* minVal(Node* root)
{
    Node* cur = root;
    while(cur->left)  //
        cur = cur->left;

    return cur;
}

}  // namespace Project

#endif  // FUNCTIONS_H
