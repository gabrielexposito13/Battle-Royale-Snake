#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu() : m_options{ MenuOptions::SinglePlayer } {
		m_font.loadFromFile("ARCADECLASSIC.TTF");
	}
	void render(sf::RenderWindow& window);
	void processEvent(sf::RenderWindow& window, sf::Event& event);
	enum MenuOptions {
		SinglePlayer,
		BattleRoyal
	};
	MenuOptions m_options;
private:
	sf::Font m_font;
};

#endif