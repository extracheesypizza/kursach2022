#ifndef NODE_HPP
#define NODE_HPP

namespace Project
{
class Node
{
   public:
    Node(int x) : key(x), height(1), right(nullptr), left(nullptr){};

    int updateAllHeights();

    int key;
    Node* right;
    Node* left;
    int height;
};
}  // namespace Project
#endif  // NODE_HPP
