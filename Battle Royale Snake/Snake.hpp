#ifndef SNAKE_HPP
#define SNAKE
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
//#include <mutex>

class Snake {
public:
	Snake() {
		sf::RectangleShape head;
		head.setFillColor(sf::Color::Green);
		head.setPosition(DEFAULT_SNAKE_X, DEFAULT_SNAKE_Y);
		head.setSize(sf::Vector2f(DEFAULT_SNAKE_SIZE_X, DEFAULT_SNAKE_SIZE_Y));
		m_rectangles.push_back(head);
	}
	~Snake() {
		m_rectangles.clear();
	}
	enum Direction {
		None,
		Left,
		Right,
		Up,
		Down
	};
	void render(sf::RenderWindow& window);
	bool hasConsumedFood(const sf::RectangleShape& food) const;
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void grow();
	sf::Vector2f getHeadPosition() const;
	Snake::Direction getDirection() const;
	void setDirection(Snake::Direction direction);
	bool hasEatenItSelf() const;
	void verifyEatenItSelf();
private:
	Direction m_currentDirection = Direction::None;
	std::vector<sf::RectangleShape> m_rectangles = {};
	bool m_hasEaten = false;
	bool m_hasEatenItSelf = false;
};

#endif