#ifndef TOS_WILL_H
#define TOS_WILL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Will {
private:
    sf::RectangleShape willBox;
    int fontSize = 32;
    sf::Text lineText;
    sf::Font font;

public:
    std::vector <std::string> lines;
    Will();
    ~Will();
    void draw(sf::RenderWindow &window);
};

#endif // TOS_WILL_H