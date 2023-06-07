#include "Application.hpp"

namespace Project
{
void Application::execute()
{
    Viewer view_;
    AVLTree tree_(view_.modelPort());
    Controller control_(&tree_, view_.controllerPort());

    while(view_.window_->isOpen())
    {
        sf::Event event;
        while(view_.window_->pollEvent(event))  //
            control_.handleEvent(event);
    }
}
}  // namespace Project
