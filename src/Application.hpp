#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Controller.hpp"

namespace Project
{
class Application
{
   private:
    Viewer view_;
    AVLTree tree_;
    Controller control_;

    sf::RenderWindow* window_;

   public:
    Application() : control_(&tree_)
    {
        tree_.subscribe(view_.modelPort());
        control_.subscribe(view_.controllerPort());
    };
    void execute();
};

}  // namespace Project
#endif  // APPLICATION_HPP
