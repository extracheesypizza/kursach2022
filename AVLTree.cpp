#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

#include "Viewer.cpp"

namespace Project
{
class AVLTree
{
   public:
    AVLTree(){};
    AVLTree(Viewer* view) : root_(nullptr) { vSubscribers_.push_back(view); };
    ~AVLTree();

    // Frames
    void updateText(std::string command);
    void updateScreen(Node* root, std::string command);
    void closeWindow();
    void resize(int width, int height);

    // Observers
    void addViewer(Viewer* view) { vSubscribers_.push_back(view); }
    void removeViewer(Viewer* view) { vSubscribers_.erase(find(vSubscribers_.begin(), vSubscribers_.end(), view)); }

    // Utilities
    void setCmdCommand(std::string s);

    // AVL-Trees
    void insert(int key)
    {
        root_ = insert(root_, key);
        root_->updateAllHeights();
        updateScreen(root_, "");
        notify();
    }

    void remove(int key)
    {
        root_ = remove(root_, key);
        root_->updateAllHeights();
        updateScreen(root_, "");
        notify();
    }

   private:
    Node* root_;
    std::vector<std::string> cmd_;
    std::vector<Viewer*> vSubscribers_;
    void notify();

    sf::Text command_;
    sf::Text typeCommand_;

    void clear(Node* root);
    static int balanceFactor(Node* cur);
    Node* returnRoot() { return root_; }
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* balanceIfNeeded(Node* node);

    Node* insert(Node* node, int key)
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

    Node* remove(Node* node, int key)
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
};

void AVLTree::notify()
{
    if(!cmd_.empty())
    {
        if(cmd_[0] == "TEXT")
            for(Viewer* v : vSubscribers_)  //
                v->setText(cmd_[cmd_.size() - 1]);

        else if(cmd_[0] == "CLOSE")
            for(Viewer* v : vSubscribers_)  //
                v->window_->close();

        else if(cmd_[0] == "RESIZE")
            for(Viewer* v : vSubscribers_)  //
                v->handleResize(toInt(cmd_[cmd_.size() - 2]), toInt(cmd_[cmd_.size() - 1]), root_);

        else if(cmd_[0] == "FRAME")
            for(Viewer* v : vSubscribers_)  //
                v->updateFrame(root_);
    }
}

void AVLTree::setCmdCommand(std::string s)
{
    if(cmd_.size() == 0)
        cmd_.push_back(s);
    else
        cmd_[0] = s;
}

void AVLTree::resize(int width, int height)
{
    setCmdCommand("RESIZE");
    cmd_.push_back(std::to_string(width));
    cmd_.push_back(std::to_string(height));
    notify();
}

void AVLTree::closeWindow()
{
    setCmdCommand("CLOSE");
    notify();
}

void AVLTree::updateText(std::string command)
{
    setCmdCommand("TEXT");
    cmd_.push_back(command);
    notify();
}

void AVLTree::updateScreen(Node* root, std::string command)
{
    setCmdCommand("FRAME");
    cmd_.push_back(command);
    notify();
    updateText(command);
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

        if(bf > 1 && balanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if(bf < -1 && balanceFactor(node->right) <= 0)
            return leftRotate(node);

        if(bf < -1 && balanceFactor(node->right) > 0)
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

int AVLTree::balanceFactor(Node* cur)
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

AVLTree::~AVLTree() { clear(root_); }

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
}  // namespace Project
#endif  // AVLTREE_H
