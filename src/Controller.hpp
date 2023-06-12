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

    // Observer
    void subscribe(Observer<vector<string>>* obs) { out_.subscribe(obs); }

   private:
    // Utility
    void setMsgCommand(std::string s);

    // Signals
    Observable<vector<string>> out_ = [this]() { return msg_; };
    void handleClose();
    void processCommand();
    void handleResize();
    void handleKeyPress(sf::Event event);
    void handleTextEntered(sf::Event event);

    // Observer
    void notifyModel();
    void notifyViewer();

    std::string command_;
    std::vector<std::string> msg_;
    AVLTree* tree_;
};

}  // namespace Project
#endif  // CONTROLLER_HPP
