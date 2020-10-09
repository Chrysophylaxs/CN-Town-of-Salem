#ifndef TOS_CHAT_H
#define TOS_CHAT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Chat {
private:
	const int border = 5;
	const int historyLength = 20;
	const int fontSize = 16;
	int height;

	sf::RectangleShape historyBox;
	sf::RectangleShape inputBox;

	sf::Text inputText;
	sf::Text historyText;
	sf::Font font;
	std::vector<std::string> history;

public:
	Chat();
	~Chat();

	void push(std::string message);
	void draw(sf::RenderWindow &window);
    void input(std::string text);
    void up();
    void down();
};

#endif // TOS_CHAT_H