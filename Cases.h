#ifndef CASES_H
#define CASES_H

#include "AVLTree.h"
#include "Viewer.h"

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
    // print(tree.returnRoot());

    cout << endl << "DELETING " << endl;
    tree.remove(40);
    tree.remove(50);
    tree.remove(20);
    // tree.print(tree.returnRoot());
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
    // tree.print(tree.returnRoot());
}

#endif  // CASES_H
