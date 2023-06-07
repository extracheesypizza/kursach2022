#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Controller.hpp"

namespace Project
{
class Application
{
   private:
    Viewer view_();
    AVLTree tree_();
    Controller control_();

    sf::RenderWindow* window_;

   public:
    Application(){};
    void execute();
};

}  // namespace Project
#endif  // APPLICATION_HPP
