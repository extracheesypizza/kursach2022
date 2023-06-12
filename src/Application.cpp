#include "Application.hpp"

namespace Project
{
void Application::execute()
{
    while(view_.window_->isOpen())
    {
        sf::Event event;

        while(view_.window_->pollEvent(event))  //
            control_.handleEvent(event);
    }
}
}  // namespace Project
