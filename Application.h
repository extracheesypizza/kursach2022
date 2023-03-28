#ifndef APPLICATION_H
#define APPLICATION_H

#include "Controller.h"

class Application
{
   public:
    void run();
};

void Application::run()
{
    Viewer view;
    AVLTree tree;
    Controller control(&view, &tree);
}

#endif  // APPLICATION_H
