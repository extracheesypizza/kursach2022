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
        {
            _tree->insert(stoi(command[1]));
        }

        else if(command[0] == "DEL")
        {
            updateAllHeights(_tree->returnRoot());
            _tree->remove(stoi(command[1]));
        }

        //        else if(command[0] == "PRINT")
        //            _view->print(_tree->returnRoot());

        else if(command[0] == "QUIT")
        {
            cout << "See you next time!" << endl;
            break;
        }
        else
        {
            cout << "Please, input a propper command." << endl;
        }

        // Viewer then outputs the tree
        cout << endl;
        _view->print(_tree->returnRoot());
        cout << endl;

        // ask Viewer for the next command
        command = _view->inputCommand();
    }
}

#endif  // CONTROLLER_H
