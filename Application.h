#ifndef APPLICATION_H
#define APPLICATION_H

#include "AVLTree.h"
#include "Cases.h"
#include "Controller.h"

class Application
{
   public:
    void run();
};

void Application::run()
{
    Controller control;
    Viewer view;
    AVLTree tree;
    control.exec(tree);
}

#endif  // APPLICATION_H
