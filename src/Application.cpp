#include "Application.hpp"

namespace Project
{
Application::Application() : control_(&tree_)
{
    tree_.subscribe(view_.modelPort());
    control_.subscribe(view_.controllerPort());
};

void Application::execute()
{
    while(view_.isOpen())
    {
        sf::Event event;

        while(view_.pollEvent(event))  //
            control_.handleEvent(event);
    }
}
}  // namespace Project
