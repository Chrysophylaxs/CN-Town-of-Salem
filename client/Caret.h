#ifndef TOS_CARET_H
#define TOS_CARET_H

#include <SFML/Graphics.hpp>

class Caret {
private:
    sf::RectangleShape caret;
    int caretPos;
    int caretHeight;
    int xCaret = 783;
    int yCaret = 516;
    int offset = 18;
    int size = 32;
    int onoff = 0;

public:
    Caret();
    ~Caret();

    int getPos();
    int getHeight();
    void up();
    void down();
    void left();
    void right();
    void reset();
    void on();
    void off();
    void draw(sf::RenderWindow &window);
    void chat();
    void will();
    void tick();
};

#endif // TOS_CARET_H
