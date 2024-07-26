#include "Snake.hpp"
#include "Constants.hpp"


void Snake::render(sf::RenderWindow& window) {
	window.clear();
	for (size_t index = 0; index < m_rectangles.size(); index++) {
		auto& rectangle = m_rectangles[index];
		auto postion = rectangle.getPosition();
		window.draw(rectangle);
	}
}

bool Snake::hasConsumedFood(const sf::RectangleShape& food) const
{
	auto snake = m_rectangles.front();
	return food.getGlobalBounds().intersects(snake.getGlobalBounds());
}


//TODO: Snake body following doesn't work

void Snake::moveLeft() {
	sf::Vector2f priorPosition;
	for (size_t index = 0; index < m_rectangles.size(); index++) {
		auto& rectangle = m_rectangles[index];
		auto postion = rectangle.getPosition();
		auto size = rectangle.getSize();
		priorPosition = postion;
		if (index == 0) {
			rectangle.setPosition(postion.x - size.x, postion.y);
		}
		else
			rectangle.setPosition(priorPosition);
	}
	m_currentDirection = Direction::Left;
}

void Snake::moveRight() {
	sf::Vector2f priorPosition;
	for (size_t index = 0; index < m_rectangles.size(); index++) {
		auto& rectangle = m_rectangles[index];
		auto postion = rectangle.getPosition();
		auto size = rectangle.getSize();
		priorPosition = postion;
		if (index == 0) {
			rectangle.setPosition(postion.x + size.x, postion.y);
		}
		else
			rectangle.setPosition(priorPosition);
	}
	m_currentDirection = Direction::Right;
}

void Snake::moveUp() {
	sf::Vector2f priorPosition;
	for (size_t index = 0; index < m_rectangles.size(); index++) {
		auto& rectangle = m_rectangles[index];
		priorPosition = rectangle.getPosition();
		auto postion = rectangle.getPosition();
		auto size = rectangle.getSize();
		priorPosition = postion;
		if (index == 0) {
			rectangle.setPosition(postion.x, postion.y - size.y);
		}
		else
			rectangle.setPosition(priorPosition);
	}
	m_currentDirection = Direction::Up;
}

void Snake::moveDown() {
	sf::Vector2f priorPosition;
	for (size_t index = 0; index < m_rectangles.size(); index++) {
		auto& rectangle = m_rectangles[index];
		auto postion = rectangle.getPosition();
		auto size = rectangle.getSize();
		priorPosition = postion;
		if (index == 0) {
			rectangle.setPosition(postion.x, postion.y + size.y);
		}
		else
			rectangle.setPosition(priorPosition);
	}
	m_currentDirection = Direction::Down;
}

void Snake::grow()
{
	auto head = m_rectangles.front();
	auto headPosition = head.getPosition();
	auto headSize = head.getSize();
	sf::RectangleShape newHead;
	newHead.setFillColor(sf::Color::Green);
	switch (m_currentDirection) {
		case Snake::Direction::Left: {
			newHead.setPosition(headPosition.x - headSize.x, headPosition.y);
			break;
		}
		case Snake::Direction::Right: {
			newHead.setPosition(headPosition.x + headSize.y, headPosition.y);
			break;
		}
		case Snake::Direction::Up: {
			newHead.setPosition(headPosition.x, headPosition.y - headSize.y);
			break;
		}
		case Snake::Direction::Down: {
			newHead.setPosition(headPosition.x, headPosition.y + headSize.y);
			break;
		}
	}
	newHead.setSize(sf::Vector2f(10, 10));
	m_rectangles.insert(m_rectangles.begin(), newHead);
}

sf::Vector2f Snake::getHeadPosition() const
{
	auto& rectangle = m_rectangles.front();
	return rectangle.getPosition();
}

void Snake::setDirection(Snake::Direction direction)
{
	m_currentDirection = direction;
}

Snake::Direction Snake::getDirection() const
{
	return m_currentDirection;
}
