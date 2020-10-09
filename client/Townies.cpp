#include "Townies.h"

Townies::Townies() {
    towniesBox.setPosition(1612, 505);
    towniesBox.setSize(sf::Vector2f(298, 500));
    towniesBox.setFillColor(sf::Color(50, 50, 50, 210));

    font.loadFromFile("consola.ttf");

    roleName.setPosition(1617, 515);
    roleName.setStyle(1);
    roleName.setFont(font);
    roleName.setCharacterSize(18);
    roleName.setFillColor(sf::Color::White);

    mafiaBox.setPosition(1347, 217);
    mafiaBox.setSize(sf::Vector2f(250, 250));
    mafiaBox.setFillColor(sf::Color(50, 50, 50, 210));
    mafiaBox.setOutlineThickness(5);
    mafiaBox.setOutlineColor(sf::Color(124, 76, 46));

    mafiaName.setPosition(1357, 262);
    mafiaName.setStyle(1);
    mafiaName.setFont(font);
    mafiaName.setCharacterSize(18);
    mafiaName.setFillColor(sf::Color::White);

    mafiaLogo.setString("Mafia:");
    mafiaLogo.setPosition(1357, 222);
    mafiaLogo.setStyle(1);
    mafiaLogo.setFont(font);
    mafiaLogo.setCharacterSize(32);
    mafiaLogo.setFillColor(sf::Color::Red);
}
Townies::~Townies() = default;

void Townies::setup(std::vector<std::string> input) {
    townies.clear();
    for (int i = 0; i < input.size(); i++) {
        //clickboxes
        sf::RectangleShape temp;
        temp.setPosition(1712, 515);
        temp.setSize(sf::Vector2f(50, 25));
        temp.setFillColor(sf::Color(50, 50, 50, 210));
        temp.setOutlineThickness(3);
        temp.setOutlineColor(sf::Color::White);
        clickboxes.push_back(temp);
        clickboxes.at(i).setPosition(1825,515 + (32 * i));
        towniesBox.setOutlineThickness(5);
        towniesBox.setOutlineColor(sf::Color(124, 76, 46));

        //townies
        townies.push_back(input.at(i));
        townies.at(i) = (std::to_string(i+1) + "." + townies.at(i));

        //click vector
        clicked.push_back(false);
    }
}

void Townies::clickboxesOn() {
    showBoxes = true;
}

void Townies::clickboxesOff() {
    showBoxes = false;
}

void Townies::setMafia(std::vector<std::string> inputMafia, bool mafia) {
    mafias.clear();
    if (mafia) {
        showMafiaBoxes = true;
        for (int i = 0; i < inputMafia.size(); ++i) {
            mafias.push_back(inputMafia.at(i));
        }
    }
}

void Townies::draw(sf::RenderWindow &window) {
    //if mafia
    if (showMafiaBoxes) {
        window.draw(mafiaBox);
        window.draw(mafiaLogo);
        for (int i = 0; i < mafias.size(); ++i) {
            mafiaName.setString(mafias.at(i));
            mafiaName.setPosition(1357, 262 + (32 * i));
            window.draw(mafiaName);
        }
    }
    //mafia + town
    window.draw(towniesBox);
    for (int i = 0; i < townies.size(); i++) {
        roleName.setString(townies.at(i));
        roleName.setPosition(1620, 513 + (32 * i));
        window.draw(roleName);
        if (showBoxes) {
            window.draw(clickboxes.at(i));
        }
    }
}

bool Townies::checkSelected() {
    for (int i = 0; i < clicked.size(); i++) {
        if (clicked.at(i)) {
            return true;
        }
    }
    return false;
}

int Townies::clearSelected(){
    for (int i = 0; i < clicked.size(); i++) {
        if (clicked.at(i)) {
            clicked.at(i) = false;
            clickboxes.at(i).setFillColor(sf::Color(sf::Color(50, 50, 50, 210)));
            return i;
        }
    }
    return -1;
}