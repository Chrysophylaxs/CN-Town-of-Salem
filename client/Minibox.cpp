#include "Minibox.h"

Minibox::Minibox() {
    loginBox.setPosition(770, 508 - (9 * border + 2 * fontSize) / 2);
    loginBox.setSize(sf::Vector2f(400, 9 * border + 2 * fontSize));
    loginName.setSize(sf::Vector2f(400 - 4 * border, border * 2 + fontSize));
    loginName.setPosition(770 + 2 * border, loginBox.getGlobalBounds().top + 5 * border + fontSize);

    loginBox.setOutlineThickness(border);
    loginBox.setOutlineColor(sf::Color(124, 76, 46));
    loginBox.setFillColor(sf::Color(0, 0, 0, 150));
    loginName.setOutlineThickness(border);
    loginName.setOutlineColor(sf::Color(124, 76, 46));
    loginName.setFillColor(sf::Color(242, 224, 124, 75));

    font.loadFromFile("consola.ttf");

    text.setFont(font);
    text.setCharacterSize(32);
    text.setFillColor(sf::Color::White);
    text.setPosition(loginBox.getGlobalBounds().left + 3 * border, loginBox.getGlobalBounds().top + 2 * border);
    nameText.setFont(font);
    nameText.setCharacterSize(32);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(loginName.getGlobalBounds().left + 2 * border, loginName.getGlobalBounds().top + 1 * border);
}

Minibox::~Minibox() = default;

void Minibox::input(std::string name) {
    nameText.setString(name);
}

void Minibox::setText(std::string msg) {
    loginText = msg;
    text.setString(loginText);
}

void Minibox::draw(sf::RenderWindow &window) {
    window.draw(loginBox);
    window.draw(loginName);
    window.draw(text);
    window.draw(nameText);
}