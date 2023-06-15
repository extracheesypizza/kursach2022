#include "Viewer.hpp"

#include <cmath>

namespace Project
{
Viewer::Viewer() : window_(new sf::RenderWindow(sf::VideoMode(800, 600), "AVL-Tree")) { setupWindow(); }

Viewer::~Viewer() { delete window_; }

bool Viewer::isOpen() { return window_->isOpen(); }

bool Viewer::pollEvent(sf::Event& event) { return window_->pollEvent(event); }

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

        resizeNodes(spacer, nodeRadius, widthLevels, heightLevels);

        clearBuffers();

        int firstLayer = (centreY * 2 / 3) + (-1 * (heightLevels / 2) * (nodeRadius / 2 + spacer));

        nodeDrawer(root, centreX, firstLayer, nodeRadius, spacer, 2, 2, widthLevels);
    }

    else
        clearBuffers();

    drawBuffers();
    window_->display();
}

void Viewer::handleResize(Node* root)
{
    // update the view to the new size of the window and keep the center
    sf::Vector2u windowSize;
    windowSize.x = window_->getSize().x;
    windowSize.y = window_->getSize().y;

    // cout << window_->getSize().x << endl;

    if(windowSize.x < 500)
        windowSize.x = 500;

    if(windowSize.y < 500)
        windowSize.y = 500;

    window_->setSize(windowSize);
    window_->setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));

    x_ = window_->getSize().x;
    y_ = window_->getSize().y;

    drawBuffers();
    window_->display();
}

void Viewer::setText(std::string command)
{
    interfaceBuffer_.clear();

    sf::Text typeCommand_;
    typeCommand_.setFont(font_);
    typeCommand_.setCharacterSize(24);
    typeCommand_.setFillColor(sf::Color::Black);
    typeCommand_.setStyle(sf::Text::Bold);
    typeCommand_.setString("Type your command: ");

    sf::Text text_;
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Red);
    text_.setStyle(sf::Text::Bold);
    text_.setString(command);
    text_.setPosition(typeCommand_.getGlobalBounds().left + typeCommand_.getGlobalBounds().width, 0);

    interfaceBuffer_.push_back(typeCommand_);
    interfaceBuffer_.push_back(text_);

    drawBuffers();

    window_->display();
}

void Viewer::setupWindow()
{
    if(!font_.loadFromFile("arial.ttf"))
    {
        // std::cout << "ERROR LOADING FONT" << std::endl;
        return;
    }

    setText("");

    window_->setFramerateLimit(30);
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

void Viewer::clearBuffers()
{
    nodeBuffer_.clear();
    linesBuffer_.clear();
    textBuffer_.clear();
    setText("");
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
    lines[0].color = sf::Color::Black;
    if(position == 1)
        lines[1].position = sf::Vector2f(xNew, yNew);
    else if(position == 0)
        lines[1].position = sf::Vector2f(xNew, yNew);
    else
        lines[1].position = sf::Vector2f(x, y);

    lines[1].color = sf::Color::Black;
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

void Viewer::resizeNodes(int& spacer, int& radius, int widthLevels, int heightLevels)
{
    // Firstly, try to resize the spacers
    while(spacer > 5)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > window_->getSize().x || heightLevels * radius * 2 + (heightLevels - 1) * spacer > window_->getSize().y - 125)
            spacer--;
        else
            return;
    }

    // If it was not enough - decrease the size of the nodes
    while(radius > 15)
    {
        if(widthLevels * radius + (widthLevels - 1) * spacer > window_->getSize().x || heightLevels * radius * 2 + (heightLevels - 1) * spacer > window_->getSize().y - 125)
            radius--;
        else
            return;
    }
}

void Viewer::onNotifyModel(Node* n) { updateFrame(n); }

void Viewer::onNotifyController(vector<string> v)
{
    if(!v.empty())
    {
        if(v[0] == "TEXT")
            setText(v[1]);

        else if(v[0] == "ERROR")
            setText(v[v.size() - 1]);

        else if(v[0] == "RESIZE")
            handleResize(nullptr);

        else if(v[0] == "CLOSE")
            window_->close();
    }
}

}  // namespace Project
