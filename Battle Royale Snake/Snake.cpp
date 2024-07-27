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


void Snake::moveLeft() {
	sf::Vector2f priorPosition;
	auto head = m_rectangles.front();
	auto postion = head.getPosition();
	auto size = head.getSize();
	sf::RectangleShape newHead;
	newHead.setFillColor(sf::Color::Green);
	newHead.setPosition(postion.x - size.x, postion.y);
	newHead.setSize(size);
	m_rectangles.insert(m_rectangles.begin(), newHead);
	if (m_hasEaten) {
		m_hasEaten = false;
	}
	else {
		m_rectangles.pop_back();
	}
	verifyEatenItSelf();
	setDirection(Direction::Left);
}

void Snake::moveRight() {
	sf::Vector2f priorPosition;
	auto head = m_rectangles.front();
	auto postion = head.getPosition();
	auto size = head.getSize();
	sf::RectangleShape newHead;
	newHead.setSize(size);
	newHead.setFillColor(sf::Color::Green);
	newHead.setPosition(postion.x + size.x, postion.y);
	m_rectangles.insert(m_rectangles.begin(), newHead);
	if (m_hasEaten) {
		m_hasEaten = false;
	}
	else {
		m_rectangles.pop_back();
	}
	verifyEatenItSelf();
	setDirection(Direction::Right);
}

void Snake::moveUp() {
	auto head = m_rectangles.front();
	auto postion = head.getPosition();
	auto size = head.getSize();
	sf::RectangleShape newHead;
	newHead.setSize(size);
	newHead.setFillColor(sf::Color::Green);
	newHead.setPosition(postion.x, postion.y - size.y);
	m_rectangles.insert(m_rectangles.begin(), newHead);
	if (m_hasEaten) {
		m_hasEaten = false;
	}
	else {
		m_rectangles.pop_back();
	}
	verifyEatenItSelf();
	setDirection(Direction::Up);
}

void Snake::moveDown() {
	auto head = m_rectangles.front();
	auto postion = head.getPosition();
	auto size = head.getSize();
	sf::RectangleShape newHead;
	newHead.setSize(size);
	newHead.setFillColor(sf::Color::Green);
	newHead.setPosition(postion.x, postion.y + size.y);
	m_rectangles.insert(m_rectangles.begin(), newHead);
	if (m_hasEaten) {
		m_hasEaten = false;
	}
	else {
		m_rectangles.pop_back();
	}
	setDirection(Direction::Down);
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
	newHead.setSize(headSize);
	m_rectangles.insert(m_rectangles.begin(), newHead);
	m_hasEaten = true;
}

sf::Vector2f Snake::getHeadPosition() const
{
	auto& rectangle = m_rectangles.front();
	return rectangle.getPosition();
}

void Snake::setDirection(Snake::Direction direction)
{
	if (m_hasEatenItSelf) {
		m_currentDirection = direction;
		return;
	}
		
	switch (m_currentDirection) {
	case Snake::Direction::Left: {
		m_hasEatenItSelf = (direction == Snake::Direction::Right) && m_rectangles.size() > 1;
		break;
	}
	case Snake::Direction::Right: {
		m_hasEatenItSelf = (direction == Snake::Direction::Left) && m_rectangles.size() > 1;
		break;
	}
	case Snake::Direction::Up: {
		m_hasEatenItSelf = (direction == Snake::Direction::Down) && m_rectangles.size() > 1;
		break;
	}
	case Snake::Direction::Down: {
		m_hasEatenItSelf = (direction == Snake::Direction::Up) && m_rectangles.size() > 1;
		break;
	}
	}
	m_currentDirection = direction;
}

bool Snake::hasEatenItSelf() const
{
	return m_hasEatenItSelf;
}

void Snake::verifyEatenItSelf()
{
	for (size_t index = 0; (index < m_rectangles.size()) && !m_hasEatenItSelf; index++) {
		for (size_t index2 = 0; index2 < m_rectangles.size(); index2++) {
			if (index == index2)
				continue;
			auto& rectangle1 = m_rectangles[index];
			auto& rectangle2 = m_rectangles[index2];
			if (rectangle1.getGlobalBounds().intersects(rectangle2.getGlobalBounds())) {
				m_hasEatenItSelf = true;
				break;
			}
		}

	}
}

Snake::Direction Snake::getDirection() const
{
	return m_currentDirection;
}
