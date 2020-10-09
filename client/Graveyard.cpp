#include "Graveyard.h"

Graveyard::Graveyard() {
    graveyardBox.setSize(sf::Vector2f(16 * 18 + 2 * border, 19 * border + 15 * fontSize + 32));
    graveyardBox.setPosition(2 * border, 7 * border + 32);
    graveyardBox.setOutlineThickness(border);
    graveyardBox.setOutlineColor(sf::Color(124, 76, 46));
    graveyardBox.setFillColor(sf::Color(242, 224, 124, 180));

    font.loadFromFile("consola.ttf");
    grave.setFont(font);
    grave.setCharacterSize(32);
    grave.setFillColor(sf::Color::Black);
    grave.setString("Graveyard:");
    grave.setPosition(65, 8 * border + 32);
    death.setFont(font);
    death.setCharacterSize(fontSize);
    death.setFillColor(sf::Color::Black);
}

Graveyard::~Graveyard() = default;

void Graveyard::push(std::string name, std::string role) {
    deaths.push_back(name);
    roles.push_back(role);
}

void Graveyard::remove(std::string name) {
    for (int i = 0; i < deaths.size(); ++i) {
        if (deaths.at(i) == name) {
            deaths.erase(deaths.begin() + i);
            roles.erase(roles.begin() + i);
            break;
        }
    }
}

void Graveyard::draw(sf::RenderWindow &window) {
    window.draw(graveyardBox);
    window.draw(grave);
    for (int i = 0; i < deaths.size(); i++) {
        death.setString(deaths.at(i) + " (" + roles.at(i) + ")");
        death.setPosition(3 * border, 115 + i * (fontSize + border));
        window.draw(death);
    }
}