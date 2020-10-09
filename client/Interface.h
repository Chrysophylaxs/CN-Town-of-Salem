#ifndef TOS_INTERFACE_H
#define TOS_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <vector>

class Interface {
private:
    const int border = 5;
    const int fontSize = 32;
    sf::RectangleShape nameBox;
    sf::RectangleShape phaseBox;
    sf::Font font;
    sf::Text nameText;
    sf::Text phaseText;
    sf::Text innoText;
    sf::Text guiltyText;

    sf::Texture musicText;
    sf::Texture willText;
    sf::Texture dayAbilityText;
    sf::Texture leaveText;

    sf::Sprite music;
    sf::Sprite will;
    sf::Sprite dayAbility;
    sf::Sprite leave;

public:
    bool showJudge;
    sf::RectangleShape innoBox;
    sf::RectangleShape guiltyBox;
    sf::RectangleShape musicBox;
    sf::RectangleShape dayAbilityBox;
    sf::RectangleShape willBox;
    sf::RectangleShape leaveBox;
    bool jail = false;
    std::vector<std::string> townies;
    sf::RectangleShape jailBox;
    std::vector<sf::RectangleShape> jailboxes;
    std::vector<bool> clicked;
    sf::Text jaileeName;

    Interface();
    ~Interface();
    void judgingOn();
    void judgingOff();
    bool checkSelected();
    int clearSelected();
    void setTownies(std::vector<std::string> input);
    void setName(std::string text);
    void setPhase(std::string phase);
    void draw(sf::RenderWindow &window);
};

#endif // TOS_INTERFACE_H