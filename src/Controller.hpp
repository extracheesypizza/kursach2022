#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "AVLTree.hpp"

namespace Project
{
class Controller
{
   public:
    Controller(AVLTree* tree) : command_(""), tree_(tree){};
    ~Controller();

    void handleEvent(sf::Event event);

   private:
    std::string command_;
    std::vector<std::string> msg_;
    AVLTree* tree_;

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

}  // namespace Project
#endif  // CONTROLLER_HPP
