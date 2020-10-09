#include "Caret.h"

Caret::Caret() {
    caretPos = 0;
    caretHeight = 0;
    caret.setSize(sf::Vector2f(2, size));
    caret.setFillColor(sf::Color::Black);
}

Caret::~Caret() = default;

int Caret::getPos() {
    return caretPos;
}

int Caret::getHeight(){
    return caretHeight;
}

void Caret::down() {
    if (caretHeight != 14) {
        caretHeight++;
        reset();
    }
}

void Caret::up() {
    if (caretHeight != 0) {
        caretHeight--;
        reset();
    }
}

void Caret::left() {
    caretPos--;
}

void Caret::right() {
    caretPos++;
}

void Caret::reset() {
    caretPos = 0;
}

void Caret::on() {
    caret.setFillColor(sf::Color::Black);
}

void Caret::off() {
    caret.setFillColor(sf::Color::Transparent);
}

void Caret::draw(sf::RenderWindow &window) {
    caret.setPosition(xCaret + offset * caretPos, yCaret + 32 * caretHeight);
    window.draw(caret);
}

void Caret::chat() {
    xCaret = 14;
    yCaret = 984;
    size = 20;
    offset = 11;
    caret.setSize(sf::Vector2f(2, size));
}

void Caret::will() {
    xCaret = 810;
    yCaret = 152;
    offset = 18;
    size = 32;
    caret.setSize(sf::Vector2f(2, size));
}

void Caret::tick() {
    onoff++;
    if (onoff == 180) {
        onoff = 0;
        on();
    }
    if (onoff == 90) {
        off();
    }
}