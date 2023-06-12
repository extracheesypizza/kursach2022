#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Controller.hpp"

namespace Project
{
class Application
{
   public:
    Application();
    void execute();

   private:
    Viewer view_;
    AVLTree tree_;
    Controller control_;
};

}  // namespace Project
#endif  // APPLICATION_HPP
