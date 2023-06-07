#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "AVLTree.hpp"

namespace Project
{
class Controller
{
   public:
    Controller(AVLTree* tree, Observer<vector<string>>* obs) : command_(""), tree_(tree) { out_.subscribe(obs); };
    ~Controller();

    void handleEvent(sf::Event event);

   private:
    std::string command_;
    std::vector<std::string> msg_;
    AVLTree* tree_;

    // Utility
    void setMsgCommand(std::string s);

    // Signals
    Observable<vector<string>> out_ = [this]() { return msg_; };
    void handleClose();
    void processCommand();
    void handleResize(sf::Event event);
    void handleKeyPress(sf::Event event);
    void handleTextEntered(sf::Event event);
    void notifyModel();
    void notifyViewer();
};

}  // namespace Project
#endif  // CONTROLLER_HPP
