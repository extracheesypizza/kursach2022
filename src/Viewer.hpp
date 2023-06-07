#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <SFML/Graphics.hpp>

#include "Functions.hpp"
#include "Node.hpp"
#include "Observer.hpp"

using std::pair;
using std::string;
using std::vector;

namespace Project
{
class Viewer
{
   public:
    Viewer();
    ~Viewer();

    sf::RenderWindow* window_;

    Observer<Node*>* port() { return &in_; }
    Observer<vector<string>>* controllerPort() { return &inController_; }

    void setupTheWindow();
    void updateFrame(Node* root);
    void handleResize(Node* root);
    void setText(string command);

   private:
    int x_, y_;
    sf::Font font_;
    sf::Text text_, typeCommand_;

    // frame buffers
    void drawBuffers();
    void clearBuffers();
    std::vector<sf::CircleShape> nodeBuffer_;
    std::vector<sf::VertexArray> linesBuffer_;
    std::vector<sf::Text> textBuffer_;
    std::vector<sf::Text> interfaceBuffer_;

    // rendering functions
    sf::CircleShape createCircle(int radius, int xNew, int yNew);
    sf::VertexArray createLinks(int x, int y, int xNew, int yNew, int position);
    sf::Text createKey(Node* root, int xNew, int yNew, int radius);
    void nodeDrawer(Node* root, int x, int y, int radius, int spacer, int level, int position, int widthLevels);
    void getPosition(int& xNew, int& yNew, int x, int y, int radius, int spacer, int widthLevels, int level, int position);
    void resizeNodes(int& spacer, int& radius, int widthLevels, int heightLevels);

    // Observers
    void onNotifyModel(Node* n);
    Observer<Node*> in_ =                           //
        Observer<Node*>(                            //
            [this](Node* n) { onNotifyModel(n); },  //
            [this](Node* n) { onNotifyModel(n); },  //
            [this](Node* n) { ; });                 //

    void onNotifyController(vector<string> v);
    Observer<vector<string>> inController_ =                      //
        Observer<vector<string>>(                                 //
            [this](vector<string> p) { onNotifyController(p); },  //
            [this](vector<string> p) { onNotifyController(p); },  //
            [this](vector<string> p) { ; });                      //
};

}  // namespace Project
#endif  // VIEWER_HPP
