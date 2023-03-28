#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

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

        // for(int i = 0; i < 2047; i++) _tree->insert(i);

        cout << "Type 'HELP' to get a How-to page;" << endl << endl;
        exec();
    }

    void exec();

    void processCommand(string command);
};

void Controller::processCommand(string command)
{
    // split the command into words
    std::vector<std::string> out;
    std::stringstream ss(command);
    std::string s;
    while(std::getline(ss, s, ' '))
    {
        out.push_back(s);
    }

    // take the action
    if(out[0] == "ADD")
        _tree->insert(stoi(out[1]));

    else if(out[0] == "DEL")
        _tree->remove(stoi(out[1]));

    else if(out[0] == "HELP")
        _view->printHelp();

    else
        cout << "Input a proper command." << endl;

    // output via text
    Node* root = _tree->returnRoot();
    if(root)
    {
        cout << endl;
        _view->print(root);
        cout << endl;
    }
}

void Controller::exec()
{
    // create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    _view->_window = &window;
    _view->setFont();

    sf::Text text;
    text.setFont(_view->_font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);

    sf::Text typeCommand;
    typeCommand.setFont(_view->_font);
    typeCommand.setCharacterSize(24);
    typeCommand.setFillColor(sf::Color::Black);
    typeCommand.setStyle(sf::Text::Bold);
    typeCommand.setString("Type your command: ");

    // string for commands
    string command;

    // logic cycle
    while(_view->_window->isOpen())
    {
        sf::Event event;
        while(_view->_window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if(event.type == sf::Event::Closed)
                _view->_window->close();

            // entering the command
            if(event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode >= 48 && event.text.unicode < 128)
                {
                    command += static_cast<char>(event.text.unicode);
                    text.setString(command);
                }
            }
            if(event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window and keep the center
                sf::Vector2u windowSize;
                if(event.size.width < 500 && event.size.height > 500)
                {
                    windowSize.x = 501;
                    windowSize.y = event.size.height;
                    _view->_window->setSize(windowSize);
                }
                else if(event.size.width < 500 && event.size.height < 500)
                {
                    windowSize.x = 501;
                    windowSize.y = 501;
                    _view->_window->setSize(windowSize);
                }
                else if(event.size.width > 500 && event.size.height < 500)
                {
                    windowSize.x = event.size.width;
                    windowSize.y = 501;
                    _view->_window->setSize(windowSize);
                }
                else
                {
                    windowSize.x = event.size.width;
                    windowSize.y = event.size.height;
                    _view->_window->setSize(windowSize);
                }

                window.setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));
                _view->_x = window.getSize().x;
                _view->_y = window.getSize().y;
                _view->updateScreen(_tree->returnRoot());
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    command += ' ';
                    text.setString(command);
                }
                if(event.key.code == sf::Keyboard::Enter)
                {
                    if(!command.empty())
                    {
                        processCommand(command);
                        cout << command << endl;
                        command = "";
                        text.setString(command);
                        _view->updateScreen(_tree->returnRoot());
                    }
                }
                if(event.key.code == sf::Keyboard::Backspace && command.size() != 0)
                {
                    command.erase(command.size() - 1);
                    text.setString(command);
                }
            }

            // clear the window with black color
            _view->_window->clear(sf::Color::White);

            // draw command line
            text.setPosition(typeCommand.getGlobalBounds().left + typeCommand.getGlobalBounds().width, 0);
            _view->_window->draw(typeCommand);
            _view->_window->draw(text);

            _view->drawBuffers();

            // end the current frame
            _view->_window->display();
        }
    }
}

#endif  // CONTROLLER_H
