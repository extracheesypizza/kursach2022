#ifndef VIEWER_HPP
#define VIEWER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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
    sf::RenderWindow* window_;

    Observer<pair<vector<string>, Node*>>* port() { return &in_; }

    void setupTheWindow();
    void updateFrame(Node* root);
    void handleResize(int width, int height, Node* root);
    void setText(string command);

   private:
    int x_;
    int y_;
    sf::Font font_;
    sf::Text text_;
    sf::Text typeCommand_;

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
    void resizeNodes(int& spacer, int& radius, int widthLevels);

    // Observer
    void onNotify(std::pair<vector<string>, Node*> v);
    Observer<std::pair<vector<string>, Node*>> in_ =                      //
        Observer<std::pair<vector<string>, Node*>>(                       //
            [this](std::pair<vector<string>, Node*> p) { ; },             //
            [this](std::pair<vector<string>, Node*> p) { onNotify(p); },  //
            [this](std::pair<vector<string>, Node*> p) { ; });            //
};

}  // namespace Project
#endif  // VIEWER_H
