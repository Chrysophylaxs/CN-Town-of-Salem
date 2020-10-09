#include "Interface.h"

Interface::Interface() {
    showJudge = false;

    font.loadFromFile("consola.ttf");
    musicText.loadFromFile("MusicOnButton.png");
    dayAbilityText.loadFromFile("DayAbilityButton.png");
    willText.loadFromFile("LastWillButton.png");
    leaveText.loadFromFile("LeaveGameButton.png");

    music.setTexture(musicText);
    dayAbility.setTexture(dayAbilityText);
    will.setTexture(willText);
    leave.setTexture(leaveText);
    music.setPosition(283 + 6 * border, 0);
    dayAbility.setPosition(283 + 11 * border + fontSize, 0);
    will.setPosition(283 + 16 * border + 2 * fontSize, 0);
    leave.setPosition(283 + 21 * border + 3 * fontSize, 0);

    jailBox.setPosition(750, 200);
    jailBox.setSize(sf::Vector2f(298, 500));
    jailBox.setFillColor(sf::Color(50, 50, 50, 210));

    jaileeName.setPosition(750, 200);
    jaileeName.setStyle(1);
    jaileeName.setFont(font);
    jaileeName.setCharacterSize(18);
    jaileeName.setFillColor(sf::Color::White);

    innoText.setPosition(700, 430);
    innoText.setString("INNOCENT");
    innoText.setFont(font);
    innoText.setCharacterSize(22);
    innoText.setFillColor(sf::Color::Black);

    guiltyText.setPosition(1100, 430);
    guiltyText.setString(" GUILTY");
    guiltyText.setFont(font);
    guiltyText.setCharacterSize(22);
    guiltyText.setFillColor(sf::Color::Black);

    innoBox.setPosition(700, 400);
    innoBox.setSize(sf::Vector2f(100, 100));
    innoBox.setFillColor(sf::Color::Green);
    innoBox.setOutlineThickness(5);
    innoBox.setOutlineColor(sf::Color(124, 76, 46));

    guiltyBox.setPosition(1100, 400);
    guiltyBox.setSize(sf::Vector2f(100, 100));
    guiltyBox.setFillColor(sf::Color::Red);
    guiltyBox.setOutlineThickness(5);
    guiltyBox.setOutlineColor(sf::Color(124, 76, 46));

    nameBox.setSize(sf::Vector2f(16 * 18 + 2 * border, 2 * border + fontSize));
    nameBox.setPosition(2 * border, 2 * border);
    nameBox.setOutlineThickness(border);
    nameBox.setOutlineColor(sf::Color(124, 76, 46));
    nameBox.setFillColor(sf::Color(242, 224, 124, 180));
    musicBox.setSize(sf::Vector2f(2 * border + fontSize, 2 * border + fontSize));
    musicBox.setPosition(16 * 18 + 7 * border, 2 * border);
    musicBox.setOutlineThickness(border);
    musicBox.setOutlineColor(sf::Color(124, 76, 46));
    musicBox.setFillColor(sf::Color(242, 224, 124, 180));
    dayAbilityBox.setSize(sf::Vector2f(2 * border + fontSize, 2 * border + fontSize));
    dayAbilityBox.setPosition(16 * 18 + 12 * border + fontSize, 2 *border);
    dayAbilityBox.setOutlineThickness(border);
    dayAbilityBox.setOutlineColor(sf::Color(124, 76, 46));
    dayAbilityBox.setFillColor(sf::Color(242, 224, 124, 180));
    willBox.setSize(sf::Vector2f(2 * border + fontSize, 2 * border + fontSize));
    willBox.setPosition(16 * 18 + 17 * border + 2 * fontSize, 2 * border);
    willBox.setOutlineThickness(border);
    willBox.setOutlineColor(sf::Color(124, 76, 46));
    willBox.setFillColor(sf::Color(242, 224, 124, 180));
    leaveBox.setSize(sf::Vector2f(2 * border + fontSize, 2 * border + fontSize));
    leaveBox.setPosition(16 * 18 + 22 * border + 3 * fontSize, 2 * border);
    leaveBox.setOutlineThickness(border);
    leaveBox.setOutlineColor(sf::Color(124, 76, 46));
    leaveBox.setFillColor(sf::Color(242, 224, 124, 180));
    phaseBox.setSize(sf::Vector2f(16 * 18 + 2 * border, 2 * border + fontSize));
    phaseBox.setPosition(1920 - 16 * 18 - 4 * border, 2 * border);
    phaseBox.setOutlineThickness(border);
    phaseBox.setOutlineColor(sf::Color(124, 76, 46));
    phaseBox.setFillColor(sf::Color(242, 224, 124, 180));

    nameText.setFont(font);
    nameText.setCharacterSize(fontSize);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(3 * border, 2 * border);
    phaseText.setFont(font);
    phaseText.setCharacterSize(fontSize);
    phaseText.setFillColor(sf::Color::Black);
    phaseText.setPosition(1920 - 16 * 18 - 3 * border, 2 * border);
}

Interface::~Interface() = default;

void Interface::setName(std::string text) {
    nameText.setString(text);
}

void Interface::setPhase(std::string phase) {
    phaseText.setString(phase);
}

void Interface::judgingOn() {
    showJudge = true;
}

void Interface::judgingOff() {
    showJudge = false;
}

void Interface::setTownies(std::vector<std::string> input) {
    townies.clear();
    for (int i = 0; i < input.size(); i++) {
        //clickboxes
        sf::RectangleShape temp;
        temp.setSize(sf::Vector2f(50, 25));
        temp.setFillColor(sf::Color(50, 50, 50, 210));
        temp.setOutlineThickness(3);
        temp.setOutlineColor(sf::Color::White);
        jailboxes.push_back(temp);
        jailboxes.at(i).setPosition(970, 210 + (32 * i));
        jailBox.setOutlineThickness(5);
        jailBox.setOutlineColor(sf::Color(124, 76, 46));

        //townies
        townies.push_back(input.at(i));
        townies.at(i) = (std::to_string(i+1) + "." + townies.at(i));

        //click vector
        clicked.push_back(false);
    }
}

bool Interface::checkSelected() {
    for (int i = 0; i < clicked.size(); i++) {
        if (clicked.at(i)) {
            return true;
        }
    }
    return false;
}

int Interface::clearSelected(){
    for (int i = 0; i < clicked.size(); i++) {
        if (clicked.at(i)) {
            clicked.at(i) = false;
            jailboxes.at(i).setFillColor(sf::Color(sf::Color(50, 50, 50, 210)));
            return i;
        }
    }
    return -1;
}

void Interface::draw(sf::RenderWindow &window) {
    window.draw(nameBox);
    window.draw(nameText);
    window.draw(musicBox);
    window.draw(dayAbilityBox);
    window.draw(willBox);
    window.draw(leaveBox);
    window.draw(phaseBox);
    window.draw(phaseText);
    window.draw(music);
    window.draw(dayAbility);
    window.draw(will);
    window.draw(leave);
    if (showJudge) {
        window.draw(innoBox);
        window.draw(innoText);
        window.draw(guiltyBox);
        window.draw(guiltyText);
    }
    if (jail) {
        window.draw(jailBox);
        for (int i = 0; i < townies.size(); i++) {
            jaileeName.setString(townies.at(i));
            jaileeName.setPosition(755, 210 + (32 * i));
            window.draw(jaileeName);
            window.draw(jailboxes.at(i));
        }
    }
}