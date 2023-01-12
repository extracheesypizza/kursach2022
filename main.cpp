#include <iostream>
#include "AVLTree.h"

using namespace std;

bool debugger = 0;

int main()
{
    AVLTree tree;

    // MY CASE 1
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // MY CASE 2
    //    tree.insert(30);
    //    tree.insert(20);
    //    tree.insert(25);
    //    tree.insert(40);
    //    tree.insert(50);
    //    tree.insert(75);
    //    tree.insert(55);
    //    tree.insert(80);
    //    tree.insert(85);
    //    tree.insert(90);

    cout << "TREE BUILDING STOPPED " << endl << endl;

    tree.print(tree.root);
}
