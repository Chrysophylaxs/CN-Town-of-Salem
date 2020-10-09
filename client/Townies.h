#ifndef TOS_TOWNIES_H
#define TOS_TOWNIES_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Townies {
private:
    std::vector<std::string> mafias;
    sf::Text mafiaName;
    sf::Text mafiaLogo;
    std::vector<std::string> townies;
    int fontSize = 16;

    sf::Text roleName;
    sf::Font font;

public:
    bool showBoxes;
    bool showMafiaBoxes = false;
    sf::RectangleShape mafiaBox;
    sf::RectangleShape towniesBox;
    std::vector<sf::RectangleShape> clickboxes;
    std::vector<bool> clicked;
    Townies();
    ~Townies();
    void setMafia(std::vector<std::string> inputMafia, bool mafia);
    bool checkSelected();
    int clearSelected();
    void clickboxesOn();
    void clickboxesOff();
    void setup(std::vector<std::string> input);
    void draw(sf::RenderWindow &window);
};

#endif // TOS_TOWNIES_H