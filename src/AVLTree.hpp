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
    Node* root_;

    void clear(Node* root);
    int balanceFactor(Node* cur) const;
    Node* returnRoot() const { return root_; }

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);

    Node* balanceIfNeeded(Node* node);

    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);

    // Observer
    Observable<Node*> out_ = [this]() { return root_; };
    void notify();
};

}  // namespace Project
#endif  // AVLTREE_HPP
