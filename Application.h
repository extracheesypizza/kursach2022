#ifndef APPLICATION_H
#define APPLICATION_H

#include "AVLTree.h"

void case1(AVLTree tree)
{
    // CASE 1
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "TREE BUILDING STOPPED " << endl << endl;
    tree.print(tree._root);

    cout << endl << "DELETING " << endl;
    tree.remove(40);
    tree.remove(50);
    tree.remove(20);
    tree.print(tree._root);
}

void case2(AVLTree tree)
{
    // CASE 2
    tree.insert(30);
    tree.insert(20);
    tree.insert(25);
    tree.insert(40);
    tree.insert(50);
    tree.insert(75);
    tree.insert(55);
    tree.insert(80);
    tree.insert(85);
    tree.insert(90);

    cout << "TREE BUILDING STOPPED " << endl << endl;
    tree.print(tree._root);
}

class Application
{
   public:
    void run();
};

void Application::run()
{
    AVLTree tree;
    case1(tree);
}

#endif  // APPLICATION_H
