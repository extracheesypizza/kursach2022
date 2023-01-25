#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <map>
#include <sstream>
#include <vector>

#include "AVLTree.h"

class Controller
{
   public:
    void exec(AVLTree tree);
};

vector<string> inputCommand()
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

void Controller::exec(AVLTree tree)
{
    vector<string> command = inputCommand();

    while(command[0] != "QUIT")
    {
        if(command[0] == "ADD")
            tree.insert(stoi(command[1]));

        else if(command[0] == "DEL")
        {
            updateAllHeights(tree._root);
            tree.remove(stoi(command[1]));
        }
        else if(command[0] == "PRINT")
            tree.print(tree._root);

        else if(command[0] == "QUIT")
        {
            cout << "See you next time!" << endl;
            break;
        }
        else
        {
            cout << "Please, input a propper command." << endl;
        }

        command = inputCommand();
    }
}

#endif  // CONTROLLER_H
