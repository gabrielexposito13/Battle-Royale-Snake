#include "GameLoop.hpp"
#include <string>

void GameLoop::render(sf::RenderWindow& window)
{
	
	window.clear();
	sf::Text scoreText;
	scoreText.setFont(m_font);
	scoreText.setFillColor(sf::Color::Green); // Change based on selection
	scoreText.setString(std::string("Score ") + std::to_string(m_score));
	m_snake.render(window);
	window.draw(m_food);
	window.draw(scoreText);
	window.display();
}

void GameLoop::processEvent(sf::RenderWindow& window, sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_snake.setDirection(Snake::Direction::Up);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_snake.setDirection(Snake::Direction::Left);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_snake.setDirection(Snake::Direction::Down);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_snake.setDirection(Snake::Direction::Right);
	}

	if (m_snake.hasConsumedFood(m_food)) {
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
		m_score += 10;
		m_snake.grow();
	}
}

void GameLoop::moveSnake()
{
	switch (m_snake.getDirection()) {
		case Snake::Direction::Left: {
			m_snake.moveLeft();
			break;
		}
		case Snake::Direction::Right: {
			m_snake.moveRight();
			break;
		}
		case Snake::Direction::Up: {
			m_snake.moveUp();
			break;
		}
		case Snake::Direction::Down: {
			m_snake.moveDown();
			break;
		}
	}
}
