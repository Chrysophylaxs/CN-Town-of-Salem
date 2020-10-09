#include "Rolecard.h"

Rolecard::Rolecard() {
    roleBox.setPosition(1612, 67);
    roleBox.setSize(sf::Vector2f(298, 400));
    roleBox.setFillColor(sf::Color(242, 224, 124, 180));
    roleBox.setOutlineThickness(5);
    roleBox.setOutlineColor(sf::Color(124, 76, 46));
    font.loadFromFile("consola.ttf");

    roleName.setPosition(1617, 67);
    roleName.setStyle(1);
    roleName.setFont(font);
    roleName.setCharacterSize(30);
    roleName.setFillColor(sf::Color::Black);

    alignment.setPosition(1617, 112);
    alignment.setFont(font);
    alignment.setCharacterSize(20);
    alignment.setFillColor(sf::Color::Black);

    ability.setString("Abilities:");
    ability.setPosition(1617, 147);
    ability.setFont(font);
    ability.setCharacterSize(20);
    ability.setFillColor(sf::Color::Black);

    ability1.setPosition(1617, 182);
    ability1.setFont(font);
    ability1.setCharacterSize(16);
    ability1.setFillColor(sf::Color::Black);

    ability2.setPosition(1617, 213);
    ability2.setFont(font);
    ability2.setCharacterSize(16);
    ability2.setFillColor(sf::Color::Black);

    attributes.setString("Attributes:");
    attributes.setPosition(1617, 244);
    attributes.setFont(font);
    attributes.setCharacterSize(20);
    attributes.setFillColor(sf::Color::Black);

    attributes1.setPosition(1617, 279);
    attributes1.setFont(font);
    attributes1.setCharacterSize(16);
    attributes1.setFillColor(sf::Color::Black);

    attributes2.setPosition(1617, 310);
    attributes2.setFont(font);
    attributes2.setCharacterSize(16);
    attributes2.setFillColor(sf::Color::Black);

    goal.setString("Goal:");
    goal.setPosition(1617, 341);
    goal.setFont(font);
    goal.setCharacterSize(20);
    goal.setFillColor(sf::Color::Black);

    goal1.setPosition(1617, 376);
    goal1.setFont(font);
    goal1.setCharacterSize(16);
    goal1.setFillColor(sf::Color::Black);

    attack.setPosition(1617, 407);
    attack.setFont(font);
    attack.setCharacterSize(20);
    attack.setFillColor(sf::Color::Black);

    defense.setPosition(1617, 442);
    defense.setFont(font);
    defense.setCharacterSize(20);
    defense.setFillColor(sf::Color::Black);
}

Rolecard::~Rolecard() = default;

void Rolecard::setRole(Role input){
    roleName.setString(input.roleName);
    alignment.setString(input.alignment);
    ability1.setString(input.ability1);
    ability2.setString(input.ability2);
    attributes1.setString(input.attributes1);
    attributes2.setString(input.attributes2);
    attack.setString(input.attack);
    defense.setString(input.defense);
    goal1.setString(input.goal);
}

void Rolecard::draw(sf::RenderWindow &window) {
    window.draw(roleBox);
    window.draw(roleName);
    window.draw(attributes);
    window.draw(attributes1);
    window.draw(attributes2);
    window.draw(ability);
    window.draw(ability1);
    window.draw(ability2);
    window.draw(alignment);
    window.draw(goal);
    window.draw(goal1);
    window.draw(attack);
    window.draw(defense);
}