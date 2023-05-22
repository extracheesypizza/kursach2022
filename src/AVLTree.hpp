#ifndef AVLTREE_HPP
#define AVLTREE_HPP
#include <iostream>
#include <vector>

#include "Viewer.hpp"

using std::pair;
using std::string;
using std::vector;

namespace Project
{
class AVLTree
{
   public:
    AVLTree(Observer<pair<vector<string>, Node*>>* obs) : root_(nullptr) { out_.subscribe(obs); };

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    AVLTree(AVLTree&&) noexcept = delete;
    AVLTree& operator=(AVLTree&&) noexcept = delete;

    // Frames
    void updateText(std::string command);
    void updateScreen(Node* root, std::string command);
    void closeWindow();
    void resize(int width, int height);

    // Utilities
    void setCmdCommand(std::string s);

    // Observer
    void subscribe(Observer<pair<vector<string>, Node*>>* obs) { out_.subscribe(obs); }

    // AVL-Trees
    void insert(int key);
    void remove(int key);

   private:
    Node* root_;
    vector<string> cmd_;
    Observable<pair<vector<string>, Node*>> out_ = [this]() { return pair(cmd_, root_); };
    sf::Text command_;
    sf::Text typeCommand_;

    void clear(Node* root);
    static int balanceFactor(Node* cur);
    Node* returnRoot() { return root_; }

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);

    Node* balanceIfNeeded(Node* node);

    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);

    void notify();
};

}  // namespace Project
#endif  // AVLTREE_H
