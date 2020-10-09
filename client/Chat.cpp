#include "Chat.h"

Chat::Chat() {
	historyBox.setPosition(2 * border, 1016 - (border * (historyLength + 6) + fontSize * historyLength) - (border * 2 + fontSize));
	historyBox.setSize(sf::Vector2f(4 * border + 69 * 11, border * (historyLength + 1) + fontSize * historyLength));
	inputBox.setSize(sf::Vector2f(4 * border + 69 * 11, border * 2 + fontSize));
	inputBox.setPosition(2 * border, 1016 - (border * 3 + fontSize) - border);
	
	historyBox.setOutlineThickness(border);
	historyBox.setOutlineColor(sf::Color(124, 76, 46));
	historyBox.setFillColor(sf::Color(0, 0, 0, 150));
	inputBox.setOutlineThickness(border);
	inputBox.setOutlineColor(sf::Color(124, 76, 46));
	inputBox.setFillColor(sf::Color(242, 224, 124, 180));

	font.loadFromFile("consola.ttf");

	historyText.setFont(font);
	historyText.setCharacterSize(20);
	historyText.setFillColor(sf::Color::White);
	inputText.setFont(font);
	inputText.setCharacterSize(20);
	inputText.setFillColor(sf::Color::Black);
	inputText.setPosition(3 * border, 1016 - (border * 3 + fontSize) - border);
	height = 0;
}

Chat::~Chat() = default;

void Chat::push(std::string text) {
    history.push_back(text);
}

void Chat::input(std::string text) {
	inputText.setString(text);
}

void Chat::draw(sf::RenderWindow &window) {
	window.draw(historyBox);
	window.draw(inputBox);
	window.draw(inputText);

	float xHistory = historyBox.getGlobalBounds().left + 2 * border;
	float yHistory = historyBox.getGlobalBounds().top + historyBox.getGlobalBounds().height - 2 * border - fontSize;

	for (int i = height; i < history.size() && i < historyLength + height; i++) {
		historyText.setString(history.at(history.size() - i - 1));
		historyText.setPosition(xHistory, yHistory - fontSize * (i - height) - border * ((i - height) + 1));
		window.draw(historyText);
	}
}

void Chat::up() {
	if (history.size() > historyLength && height < history.size() - historyLength) {
		height++;
	}
}

void Chat::down() {
	if (height > 0) {
		height--;
	}
}