#include "Controller.hpp"

namespace Project
{
Controller::~Controller()
{
    command_.clear();
    msg_.clear();
    tree_ = nullptr;
}

void Controller::notify()
{
    if(!msg_.empty())
    {
        if(msg_[0] == "ADD")
            tree_->insert(toInt(msg_[1]));

        else if(msg_[0] == "DEL")
            tree_->remove(toInt(msg_[1]));

        else if(msg_[0] == "ERROR" || msg_[0] == "TEXT")
            tree_->updateText(msg_[msg_.size() - 1]);

        else if(msg_[0] == "RESIZE")
            tree_->resize(toInt(msg_[msg_.size() - 2]), toInt(msg_[msg_.size() - 1]));

        else if(msg_[0] == "CLOSE")
            tree_->closeWindow();
    }
}

void Controller::handleEvent(sf::Event event)
{
    if(event.type == sf::Event::Closed)
        handleClose();

    else if(event.type == sf::Event::TextEntered)
        handleTextEntered(event);

    else if(event.type == sf::Event::Resized)
        handleResize(event);

    else if(event.type == sf::Event::KeyPressed)
        handleKeyPress(event);

    notify();
    msg_.clear();
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

    else if(event.key.code == sf::Keyboard::Enter && !command_.empty())
        processCommand();

    else if(event.key.code == sf::Keyboard::Backspace && command_.size() != 0)
    {
        command_.erase(command_.size() - 1);
        setMsgCommand("TEXT");
        msg_.push_back(command_);
    }
}

void Controller::handleTextEntered(sf::Event event)
{
    if(event.text.unicode >= 48 && event.text.unicode < 91)
        command_ += event.text.unicode;

    else if(event.text.unicode >= 97 && event.text.unicode < 128)
        command_ += event.text.unicode - 32;

    setMsgCommand("TEXT");
    msg_.push_back(command_);
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
