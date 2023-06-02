#include "Application.hpp"

namespace Project
{
Application::Application()
{
    view_ = new Viewer();
    tree_ = new AVLTree(view_->port());
    control_ = new Controller(tree_);
};

Application::~Application()
{
    view_ = nullptr;
    tree_ = nullptr;
    control_ = nullptr;
    window_ = nullptr;
};

void Application::execute()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "AVL-Tree");
    view_->window_ = &window;
    view_->setupTheWindow();
    view_->setupTheWindow();
    window_ = view_->window_;

    while(window_->isOpen())
    {
        sf::Event event;
        while(window_->pollEvent(event))  //
            control_->handleEvent(event);
    }
}
}  // namespace Project
