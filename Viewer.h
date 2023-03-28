#ifndef VIEWER_H
#define VIEWER_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "AVLTree.h"

using namespace std;

//
// SFML Viewer to be done.
//

class Viewer
{
   public:
    int _x;
    int _y;
    sf::Font _font;

    // frame buffers
    vector<sf::CircleShape> _nodeBuffer;
    vector<sf::VertexArray> _linesBuffer;
    vector<sf::Text> _textBuffer;

    // program window
    sf::RenderWindow* _window;

    // recieves a command
    vector<string> inputCommand();

    // setup the working font
    void setFont();

    // prints the tree 'in-order'
    void print(Node* root, bool ch = false);

    // prints the How-to page
    void printHelp();

    // Draw the tree
    void updateScreen(Node* root);

    // draw the node
    void nodeDrawer(Node* root, int x, int y, int radius, int spacer, int level, int position, int widthLevels);

    // update the screen with bufferred frames
    void drawBuffers();

    // clear the buffer to update the screen
    void clearBuffers();

    void resizeNodes(int& spacer, int& radius, int widthLevels);
};

void Viewer::setFont()
{
    if(!_font.loadFromFile("arial.ttf"))
        return;
}

void Viewer::clearBuffers()
{
    this->_linesBuffer.clear();
    this->_nodeBuffer.clear();
    this->_textBuffer.clear();
}

void Viewer::drawBuffers()
{
    for(int i = 0; i < this->_linesBuffer.size(); i++)  //
        _window->draw(this->_linesBuffer[i]);

    for(int i = 0; i < this->_nodeBuffer.size(); i++)  //
        _window->draw(this->_nodeBuffer[i]);

    for(int i = 0; i < this->_textBuffer.size(); i++)  //
        _window->draw(this->_textBuffer[i]);
}

void Viewer::nodeDrawer(Node* root, int x, int y, int radius, int spacer, int level, int position, int widthLevels)
{
    if(root)
    {
        int xNew = x;
        int yNew = y;

        if(position == 0)  // left child
        {
            xNew = x - (widthLevels / level) * (radius + spacer);
            yNew = y + spacer * 4.f + radius * 2.f;
        }
        else if(position == 1)  // right child
        {
            xNew = x + (widthLevels / level) * (radius + spacer);
            yNew = y + spacer * 4.f + radius * 2.f;
        }

        // Node Circle
        sf::CircleShape node(radius);  // RADIUS
        node.setOrigin(radius, radius);
        node.setPosition(xNew, yNew);
        node.setFillColor(sf::Color(100, 250, 50));
        node.setOutlineThickness(2);
        node.setOutlineColor(sf::Color(0, 0, 0));
        _nodeBuffer.push_back(node);

        // Links
        sf::VertexArray lines(sf::LinesStrip, 2);
        lines[0].position = sf::Vector2f(x, y);
        lines[0].color = sf::Color::Red;
        if(position == 1)
            lines[1].position = sf::Vector2f(xNew, yNew);
        else if(position == 0)
            lines[1].position = sf::Vector2f(xNew, yNew);
        else
            lines[1].position = sf::Vector2f(x, y);

        lines[1].color = sf::Color::Red;
        _linesBuffer.push_back(lines);

        // Node Text
        sf::Text nodeKey;
        nodeKey.setFont(_font);
        nodeKey.setCharacterSize(24);
        nodeKey.setFillColor(sf::Color::Black);
        nodeKey.setStyle(sf::Text::Bold);
        nodeKey.setString(to_string(root->key));

        while(nodeKey.getLocalBounds().width > radius)  // Resizing text to fit the radius
            nodeKey.setCharacterSize(nodeKey.getCharacterSize() - 1);

        nodeKey.setPosition(xNew - nodeKey.getGlobalBounds().width / 2, yNew - (nodeKey.getGlobalBounds().top + nodeKey.getGlobalBounds().height) / 2);
        _textBuffer.push_back(nodeKey);

        nodeDrawer(root->left, xNew, yNew, radius, spacer, level * 2, 0, widthLevels);
        nodeDrawer(root->right, xNew, yNew, radius, spacer, level * 2, 1, widthLevels);
    }
}

void Viewer::resizeNodes(int& spacer, int& radius, int widthLevels)
{
    // firstly, try to resize the spacers
    while(spacer > 5)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > _window->getSize().x)
            spacer--;
        else
            return;
    }

    // If it was not enough - decrease the size of the nodes
    while(radius > 15)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > _window->getSize().x)
            radius--;
        else
            return;
    }
}

void Viewer::updateScreen(Node* root)
{
    if(root)
    {
        // get levels of height
        int heightLevels = root->height;

        float heightLevelsFloat = heightLevels;

        // find width
        int widthLevels = pow(2, root->height);

        // set basic radius
        int nodeRadius = 25;

        // set spacer width
        int spacer = 10;

        // get screen centre
        int centreX = _window->getSize().x / 2.f;
        int centreY = _window->getSize().y / 2.f;

        // Y levels
        vector<int> levelsY;
        int levelsHalved = heightLevels / 2;
        for(int i = 0; i < heightLevels; i++)
        {
            int curHeight = -1 * (levelsHalved - i) * (nodeRadius / 2 + spacer);
            levelsY.push_back(centreY * 2 / 3 + curHeight);
        }

        resizeNodes(spacer, nodeRadius, widthLevels);

        clearBuffers();

        nodeDrawer(root, centreX, levelsY[0], nodeRadius, spacer, 2, 2, widthLevels);

        drawBuffers();
    }
}

vector<string> Viewer::inputCommand()
{
    cout << "Please, enter a command: ";
    vector<string> res;

    stringstream ss;
    string s;
    getline(cin, s);
    ss << s;

    string str;
    while(getline(ss, str, ' ')) res.push_back(str.c_str());

    return res;
}

// prints the tree 'in-order'
void Viewer::print(Node* root, bool ch)
{
    updateAllHeights(root);
    if(ch == false)
    {
        cout << "Key" << '\t' << "L" << '\t' << "R" << '\t' << "BF" << '\t' << "H" << endl;
        ch = true;
    }

    if(root->left)
        print(root->left, ch);

    cout << root->key << '\t';
    if(root->left)
        cout << root->left->key;
    cout << '\t';
    if(root->right)
        cout << root->right->key;
    cout << '\t';
    // cout << AVLTree::balanceFactor(root);
    cout << '\t';
    cout << root->height << endl;

    if(root->right)
        print(root->right, ch);
}

void Viewer::printHelp()
{
    cout << "==============================================" << endl;
    cout << "'ADD X' -> Adds a node with value X to the tree;" << endl;
    cout << "'DEL X' -> Removes the node with value X from the tree;" << endl;
    cout << "'QUIT' -> Stop the Execution of the program;" << endl;
    cout << "==============================================" << endl;
}

#endif  // VIEWER_H
