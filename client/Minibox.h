#ifndef TOS_MINIBOX_H
#define TOS_MINIBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class Minibox {
private:
    const int border = 5;
    const int historyLength = 15;
    const int fontSize = 32;
    std::string loginText;

    sf::RectangleShape loginBox;
    sf::RectangleShape loginName;

    sf::Text text;
    sf::Text nameText;
    sf::Font font;
public:
    Minibox();
    ~Minibox();
    void input(std::string name);
    void setText(std::string msg);
    void draw(sf::RenderWindow &window);
};

#endif // TOS_MINIBOX_H