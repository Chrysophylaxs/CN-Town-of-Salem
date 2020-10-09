#ifndef TOS_GRAVEYARD_H
#define TOS_GRAVEYARD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Graveyard {
private:
    const int border = 5;
    const int fontSize = 20;
    std::vector<std::string> deaths;
    std::vector<std::string> roles;

    sf::RectangleShape graveyardBox;
    sf::Font font;
    sf::Text grave;
    sf::Text death;

public:
    Graveyard();
    ~Graveyard();
    void push(std::string name, std::string role);
    void remove(std::string name);
    void draw(sf::RenderWindow &window);
};

#endif // TOS_GRAVEYARD_H