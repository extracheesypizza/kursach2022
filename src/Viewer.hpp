#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <SFML/Graphics.hpp>

#include "Functions.hpp"
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

    bool isOpen();
    bool pollEvent(sf::Event& event);

    Observer<Node*>* modelPort() { return &inModel_; }
    Observer<vector<string>>* controllerPort() { return &inController_; }

   private:
    // misc
    void updateFrame(Node* root);
    void handleResize(Node* root);
    void setText(string command);
    void setupWindow();

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
    Observer<Node*> inModel_ =                      //
        Observer<Node*>(                            //
            [this](Node* n) { onNotifyModel(n); },  //
            [this](Node* n) { onNotifyModel(n); },  //
            [this](Node* n) { ; });                 //

    void onNotifyController(vector<string> v);
    Observer<vector<string>> inController_ =                      //
        Observer<vector<string>>(                                 //
            [this](vector<string> v) { onNotifyController(v); },  //
            [this](vector<string> v) { onNotifyController(v); },  //
            [this](vector<string> v) { ; });                      //

    int x_, y_;
    sf::Font font_;
    sf::RenderWindow* window_;
};

}  // namespace Project
#endif  // VIEWER_HPP
