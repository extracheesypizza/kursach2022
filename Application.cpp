#ifndef APPLICATION_H
#define APPLICATION_H

#include "Controller.cpp"

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
    Application()
    {
        Viewer view;
        view_ = view;

        AVLTree tree(&view_);
        tree_ = tree;

        Controller control(&tree_);
        control_ = control;
    };

    void execute();
};

void Application::execute()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "AVL-Tree");
    view_.window_ = &window;
    view_.setupTheWindow();
    window_ = view_.window_;

    while(window_->isOpen())
    {
        sf::Event event;
        while(window_->pollEvent(event))  //
            control_.handleEvent(event);
    }
}
}  // namespace Project
#endif  // APPLICATION_H
