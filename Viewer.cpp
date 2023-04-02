#ifndef VIEWER_H
#define VIEWER_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

#include "Node.cpp"

namespace Project
{
class Viewer
{
   public:
    sf::RenderWindow* window_;

    void setupTheWindow();
    void updateFrame(Node* root);
    void handleResize(int width, int height, Node* root);
    void setText(std::string command);

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
};

void Viewer::setText(std::string command)
{
    interfaceBuffer_.clear();

    text_.setString(command);
    typeCommand_.setString("Type your command: ");

    text_.setPosition(typeCommand_.getGlobalBounds().left + typeCommand_.getGlobalBounds().width, 0);

    interfaceBuffer_.push_back(typeCommand_);
    interfaceBuffer_.push_back(text_);

    drawBuffers();
    window_->display();
}

void Viewer::setupTheWindow()
{
    if(!font_.loadFromFile("arial.ttf"))
    {
        std::cout << "ERROR LOADING FONT" << std::endl;
        return;
    }

    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Red);
    text_.setStyle(sf::Text::Bold);

    typeCommand_.setFont(font_);
    typeCommand_.setCharacterSize(24);
    typeCommand_.setFillColor(sf::Color::Black);
    typeCommand_.setStyle(sf::Text::Bold);

    setText("");

    window_->setFramerateLimit(30);
}

void Viewer::clearBuffers()
{
    nodeBuffer_.clear();
    linesBuffer_.clear();
    textBuffer_.clear();
}

void Viewer::drawBuffers()
{
    window_->clear(sf::Color::White);

    for(int i = 0; i < linesBuffer_.size(); i++)  //
        window_->draw(linesBuffer_[i]);

    for(int i = 0; i < nodeBuffer_.size(); i++)  //
        window_->draw(nodeBuffer_[i]);

    for(int i = 0; i < textBuffer_.size(); i++)  //
        window_->draw(textBuffer_[i]);

    for(int i = 0; i < interfaceBuffer_.size(); i++)  //
        window_->draw(interfaceBuffer_[i]);
}

void Viewer::getPosition(int& xNew, int& yNew, int x, int y, int radius, int spacer, int widthLevels, int level, int position)
{
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
}

sf::CircleShape Viewer::createCircle(int radius, int xNew, int yNew)
{
    sf::CircleShape node(radius);
    node.setOrigin(radius, radius);
    node.setPosition(xNew, yNew);
    node.setFillColor(sf::Color(100, 250, 50));
    node.setOutlineThickness(2);
    node.setOutlineColor(sf::Color(0, 0, 0));
    return node;
}

sf::VertexArray Viewer::createLinks(int x, int y, int xNew, int yNew, int position)
{
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
    return lines;
}

sf::Text Viewer::createKey(Node* root, int xNew, int yNew, int radius)
{
    sf::Text nodeKey;
    nodeKey.setFont(font_);
    nodeKey.setCharacterSize(24);
    nodeKey.setFillColor(sf::Color::Black);
    nodeKey.setStyle(sf::Text::Bold);
    nodeKey.setString(std::to_string(root->key));

    // Resizing text to fit the radius
    while(nodeKey.getLocalBounds().width > radius)  //
        nodeKey.setCharacterSize(nodeKey.getCharacterSize() - 1);

    nodeKey.setPosition(xNew - nodeKey.getGlobalBounds().width * 3 / 5, yNew - (nodeKey.getGlobalBounds().top + nodeKey.getGlobalBounds().height) * 3 / 5);

    return nodeKey;
}

void Viewer::nodeDrawer(Node* root, int x, int y, int radius, int spacer, int level, int position, int widthLevels)
{
    if(root)
    {
        int xNew = x;
        int yNew = y;
        getPosition(xNew, yNew, x, y, radius, spacer, widthLevels, level, position);

        nodeBuffer_.push_back(createCircle(radius, xNew, yNew));

        linesBuffer_.push_back(createLinks(x, y, xNew, yNew, position));

        textBuffer_.push_back(createKey(root, xNew, yNew, radius));

        nodeDrawer(root->left, xNew, yNew, radius, spacer, level * 2, 0, widthLevels);
        nodeDrawer(root->right, xNew, yNew, radius, spacer, level * 2, 1, widthLevels);
    }
}

void Viewer::resizeNodes(int& spacer, int& radius, int widthLevels)
{
    // Firstly, try to resize the spacers
    while(spacer > 5)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > window_->getSize().x)
            spacer--;
        else
            return;
    }

    // If it was not enough - decrease the size of the nodes
    while(radius > 15)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > window_->getSize().x)
            radius--;
        else
            return;
    }
}

void Viewer::updateFrame(Node* root)
{
    if(root)
    {
        int heightLevels = root->height;

        // find width
        int widthLevels = pow(2, root->height);

        int nodeRadius = 25;
        int spacer = 10;

        int centreX = window_->getSize().x / 2.f;
        int centreY = window_->getSize().y / 2.f;

        resizeNodes(spacer, nodeRadius, widthLevels);

        clearBuffers();

        int firstLayer = (centreY * 2 / 3) + (-1 * (heightLevels / 2) * (nodeRadius / 2 + spacer));

        nodeDrawer(root, centreX, firstLayer, nodeRadius, spacer, 2, 2, widthLevels);

        drawBuffers();

        window_->display();
    }
}

void Viewer::handleResize(int width, int height, Node* root)
{
    // update the view to the new size of the window and keep the center
    sf::Vector2u windowSize;

    if(width < 500 && height > 500)
    {
        windowSize.x = 501;
        windowSize.y = height;
        window_->setSize(windowSize);
    }
    else if(width < 500 && height < 500)
    {
        windowSize.x = 501;
        windowSize.y = 501;
        window_->setSize(windowSize);
    }
    else if(width > 500 && height < 500)
    {
        windowSize.x = width;
        windowSize.y = 501;
        window_->setSize(windowSize);
    }
    else
    {
        windowSize.x = width;
        windowSize.y = height;
        window_->setSize(windowSize);
    }

    window_->setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));

    x_ = window_->getSize().x;
    y_ = window_->getSize().y;

    updateFrame(root);
}
}  // namespace Project
#endif  // VIEWER_H
