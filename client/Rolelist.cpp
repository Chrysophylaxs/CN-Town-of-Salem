#include "Rolelist.h"

Rolelist::Rolelist() {
    rolelistBox.setSize(sf::Vector2f(213, 19 * border + 15 * fontSize + 32));
    rolelistBox.setPosition(16 * 18 + 7 * border, 7 * border + 32);
    rolelistBox.setOutlineThickness(border);
    rolelistBox.setOutlineColor(sf::Color(124, 76, 46));
    rolelistBox.setFillColor(sf::Color(242, 224, 124, 180));

    font.loadFromFile("consola.ttf");
    head.setFont(font);
    head.setCharacterSize(32);
    head.setFillColor(sf::Color::Black);
    head.setString("Role List:");
    head.setPosition(340, 8 * border + 32);
    role.setFont(font);
    role.setCharacterSize(fontSize);
    role.setFillColor(sf::Color::Black);
}

Rolelist::~Rolelist() = default;

void Rolelist::draw(sf::RenderWindow &window) {
    window.draw(rolelistBox);
    window.draw(head);
    for (int i = 0; i < 15; i++) {
        role.setString(roles[i]);
        role.setPosition(16 * 18 + 8 * border, 115 + i * (fontSize + border));
        window.draw(role);
    }
}