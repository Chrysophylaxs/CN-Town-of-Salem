#ifndef TOS_ROLELIST_H
#define TOS_ROLELIST_H

#include <SFML/Graphics.hpp>
#include <string>

class Rolelist {
private:
    const int border = 5;
    const int fontSize = 20;
    std::string roles[15] = {
        "Jailor",
        "Town Investigative",
        "Town Investigative",
        "Town Protective",
        "Town Killing",
        "Town Support",
        "Random Town",
        "Random Town",
        "Random Town",
        "Godfather",
        "Mafioso",
        "Random Mafia",
        "Random Mafia",
        "Neutral Evil",
        "Neutral Killing"
    };

    sf::RectangleShape rolelistBox;
    sf::Font font;
    sf::Text role;
    sf::Text head;

public:
    Rolelist();
    ~Rolelist();
    void draw(sf::RenderWindow &window);
};

#endif // TOS_ROLELIST_H