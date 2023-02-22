#ifndef VIEWER_H
#define VIEWER_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#include "AVLTree.h"

using namespace std;

//
// SFML Viewer to be done.
//

class Viewer
{
   public:
    // recieves a command
    vector<string> inputCommand();

    // prints the tree 'in-order'
    void print(Node* root, bool ch = false);

    // prints the How-to page
    void printHelp();
};

vector<string> Viewer::inputCommand()
{
    cout << "Please, enter a command: ";
    vector<string> res;

    stringstream ss;
    string s;
    getline(cin, s);
    ss << s;

    string str;
    while(getline(ss, str, ' ')) res.push_back(str.c_str());

    return res;
}

// prints the tree 'in-order'
void Viewer::print(Node* root, bool ch)
{
    updateAllHeights(root);
    if(ch == false)
    {
        cout << "Key" << '\t' << "L" << '\t' << "R" << '\t' << "BF" << '\t' << "H" << endl;
        ch = true;
    }

    if(root->left)
        print(root->left, ch);

    cout << root->key << '\t';
    if(root->left)
        cout << root->left->key;
    cout << '\t';
    if(root->right)
        cout << root->right->key;
    cout << '\t';
    cout << AVLTree::balanceFactor(root);
    cout << '\t';
    cout << root->height << endl;

    if(root->right)
        print(root->right, ch);
}

void Viewer::printHelp()
{
    cout << "==============================================" << endl;
    cout << "'ADD X' -> Adds a node with value X to the tree;" << endl;
    cout << "'DEL X' -> Removes the node with value X from the tree;" << endl;
    cout << "'QUIT' -> Stop the Execution of the program;" << endl;
    cout << "==============================================" << endl;
}

#endif  // VIEWER_H
