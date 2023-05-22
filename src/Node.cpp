#include "Node.hpp"

namespace Project
{
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

}  // namespace Project
