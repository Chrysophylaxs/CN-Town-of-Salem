#include "Will.h"
#include <iostream>

Will::Will() {
    font.loadFromFile("consola.ttf");
    willBox.setPosition(800, 100);
    willBox.setSize(sf::Vector2f(500, 600));
    willBox.setFillColor(sf::Color(242, 224, 124, 180));
    willBox.setOutlineThickness(5);
    willBox.setOutlineColor(sf::Color(124, 76, 46));

    lineText.setPosition(810, 150);
    lineText.setFont(font);
    lineText.setCharacterSize(fontSize);
    lineText.setFillColor(sf::Color::Black);

    for (int i = 0; i < 15; i++){
        lines.push_back("");
    }
}
Will::~Will() = default;

void Will::draw(sf::RenderWindow &window) {
    window.draw(willBox);
    for (int i = 0; i < 15; i++) {
        lineText.setString(lines.at(i));
        lineText.setPosition(810, 150 + (i * 32));
        window.draw(lineText);
    }
}