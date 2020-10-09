#ifndef TOS_ROLECARD_H
#define TOS_ROLECARD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Role.h"

class Rolecard {

private:
    int fontSize = 16;
    sf::RectangleShape roleBox;
    sf::Text roleName;
    sf::Text alignment;
    sf::Text ability;
    sf::Text ability1;
    sf::Text ability2;
    sf::Text attributes;
    sf::Text attributes1;
    sf::Text attributes2;
    sf::Text goal;
    sf::Text goal1;
    sf::Text attack;
    sf::Text defense;
    sf::Font font;

public:
    Rolecard();
    ~Rolecard();

    void setRole(Role input);
    void draw(sf::RenderWindow &window);
};

#endif // TOS_ROLECARD_H
