#ifndef GAME_LOOP_HPP
#define GAME_LOOP_HPP
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include <random>

class GameLoop {
public:
	GameLoop(bool isMultiplayer) : m_isMultiplayer{ isMultiplayer }, m_isGameOver{ false }, m_score{ 0 } {
		m_font.loadFromFile("ARCADECLASSIC.TTF");
		m_food.setFillColor(sf::Color::White);
		std::mt19937 gen32;
		gen32.seed(time(nullptr));
		uint16_t x = 0;
		uint16_t y = 0;
		do {
			x = (gen32() % WIDTH);
			y = (gen32() % HEIGHT);
		} while (x == DEFAULT_SNAKE_X && y == DEFAULT_SNAKE_Y);
		m_food.setPosition(x, y);
		m_food.setSize(sf::Vector2f(10, 10));
	}
	~GameLoop() = default;

	void render(sf::RenderWindow& window);
	void processEvent(sf::RenderWindow& window, sf::Event& event);
	void moveSnake();

private:
	bool m_isMultiplayer;
	uint64_t m_score;
	bool m_isGameOver;
	Snake m_snake;
	sf::Font m_font;
	sf::RectangleShape m_food;

};

#endif