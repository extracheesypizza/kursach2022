#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "Viewer.hpp"

using std::pair;
using std::string;
using std::vector;

namespace Project
{
class AVLTree
{
   public:
    AVLTree() : root_(nullptr){};
    ~AVLTree();

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree(AVLTree&&) noexcept = delete;
    AVLTree& operator=(AVLTree&&) noexcept = delete;

    // AVL-Tree
    void insert(int key);
    void remove(int key);

    // Observer
    void subscribe(Observer<Node*>* obs) { out_.subscribe(obs); }

   private:
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);

    Node* balanceIfNeeded(Node* node);

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);

    int balanceFactor(Node* cur) const;
    int maxHeight(Node* left, Node* right);
    Node* minVal(Node* root);
    void clear(Node* root);

    Node* returnRoot() const { return root_; }

    // Observer
    Observable<Node*> out_ = [this]() { return root_; };
    void notify();

    Node* root_;
};

}  // namespace Project
#endif  // AVLTREE_HPP
