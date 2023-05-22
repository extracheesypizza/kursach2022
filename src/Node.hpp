#ifndef NODE_HPP
#define NODE_HPP

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
}  // namespace Project
#endif  // NODE_H
