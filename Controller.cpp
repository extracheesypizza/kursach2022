#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

#include "AVLTree.cpp"

namespace Project
{
class Controller
{
   public:
    Controller(){};
    Controller(AVLTree* tree)
    {
        command_ = "";
        tSubscribers_.push_back(tree);
    };

    void handleEvent(sf::Event event);

    // Observers
    void addTree(AVLTree* tree) { tSubscribers_.push_back(tree); }
    void removeTree(AVLTree* tree) { tSubscribers_.erase(find(tSubscribers_.begin(), tSubscribers_.end(), tree)); }

   private:
    std::string command_;
    std::vector<std::string> msg_;
    std::vector<AVLTree*> tSubscribers_;

    // Utility
    void setMsgCommand(std::string s);

    // Signals
    void handleClose();
    void processCommand();
    void handleResize(sf::Event event);
    void handleKeyPress(sf::Event event);
    void handleTextEntered(sf::Event event);
    void notify();
};

bool isNumeric(std::string str)
{
    for(int i = 0; i < str.length(); i++)
        if(!isdigit(str[i]))
            return false;
    return true;
}

void Controller::notify()
{
    if(!msg_.empty())
    {
        if(msg_[0] == "ADD")
            for(AVLTree* t : tSubscribers_)  //
                t->insert(toInt(msg_[1]));

        else if(msg_[0] == "DEL")
            for(AVLTree* t : tSubscribers_)  //
                t->remove(toInt(msg_[1]));

        else if(msg_[0] == "ERROR" || msg_[0] == "TEXT")
            for(AVLTree* t : tSubscribers_)  //
                t->updateText(msg_[msg_.size() - 1]);

        else if(msg_[0] == "RESIZE")
            for(AVLTree* t : tSubscribers_)  //
                t->resize(toInt(msg_[msg_.size() - 2]), toInt(msg_[msg_.size() - 1]));

        else if(msg_[0] == "CLOSE")
            for(AVLTree* t : tSubscribers_)  //
                t->closeWindow();
    }
}

void Controller::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::Closed)
        handleClose();

    if(event.type == sf::Event::TextEntered)
        handleTextEntered(event);

    if(event.type == sf::Event::Resized)
        handleResize(event);

    if(event.type == sf::Event::KeyPressed)
        handleKeyPress(event);

    notify();
}

void Controller::setMsgCommand(std::string s)
{
    if(msg_.size() == 0)
        msg_.push_back(s);
    else
        msg_[0] = s;
}

void Controller::handleClose() { setMsgCommand("CLOSE"); }

void Controller::handleResize(sf::Event event)
{
    setMsgCommand("RESIZE");
    msg_.push_back(std::to_string(event.size.width));
    msg_.push_back(std::to_string(event.size.height));
}

void Controller::handleKeyPress(sf::Event event)
{
    if(event.key.code == sf::Keyboard::Space)
    {
        command_ += ' ';
        setMsgCommand("TEXT");
        msg_.push_back(command_);
    }

    if(event.key.code == sf::Keyboard::Enter && !command_.empty())
        processCommand();

    if(event.key.code == sf::Keyboard::Backspace && command_.size() != 0)
    {
        command_.erase(command_.size() - 1);
        setMsgCommand("TEXT");
        msg_.push_back(command_);
    }
}

void Controller::handleTextEntered(sf::Event event)
{
    if(event.text.unicode >= 48 && event.text.unicode < 128)
    {
        command_ += event.text.unicode;
        setMsgCommand("TEXT");
        msg_.push_back(command_);
    }
}

void Controller::processCommand()
{
    // split the command into words
    msg_.clear();
    std::stringstream ss(command_);
    std::string s;
    while(std::getline(ss, s, ' '))  //
        msg_.push_back(s);
    command_ = "";

    // take the action
    if(msg_[0] == "ADD" || msg_[0] == "DEL")
    {
        if(msg_.size() <= 1 || !isNumeric(msg_[1]))
        {
            msg_[0] = "ERROR";
            msg_.push_back("Enter a number!");
        }
    }

    else
    {
        msg_[0] = "ERROR";
        msg_.push_back("Wrong command!");
    }
}
}  // namespace Project
#endif  // CONTROLLER_H
