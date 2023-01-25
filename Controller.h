#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <sstream>
#include <vector>

#include "AVLTree.h"
#include "Viewer.h"

class Controller
{
    Viewer* _view;
    AVLTree* _tree;

   public:
    Controller(Viewer* view, AVLTree* tree)
    {
        _view = view;
        _tree = tree;

        cout << "Type 'HELP' to get a How-to page;" << endl << endl;
        exec();
    }
    void exec();
};

void Controller::exec()
{
    // using Viewer to recieve a command
    vector<string> command = _view->inputCommand();

    // Controller does all the logic with the Model
    while(command[0] != "QUIT")
    {
        if(command[0] == "ADD")
            _tree->insert(stoi(command[1]));

        else if(command[0] == "DEL")
            _tree->remove(stoi(command[1]));

        else if(command[0] == "HELP")
            _view->printHelp();

        else if(command[0] == "QUIT")
        {
            cout << "See you next time!" << endl;
            break;
        }

        else
            cout << "Input a proper command." << endl;

        // Viewer then outputs the tree
        Node* root = _tree->returnRoot();
        if(root)
        {
            cout << endl;
            _view->print(root);
            cout << endl;
        }

        // asks Viewer for the next command
        command = _view->inputCommand();
    }
}

#endif  // CONTROLLER_H
