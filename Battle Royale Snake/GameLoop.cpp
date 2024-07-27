#include "GameLoop.hpp"
#include <string>

void GameLoop::render(sf::RenderWindow& window)
{
	
	window.clear();
	switch (m_isGameOver) {
		case false: {
			sf::Text scoreText;
			scoreText.setFont(m_font);
			scoreText.setFillColor(sf::Color::Green); // Change based on selection
			scoreText.setCharacterSize(NON_TITLE_FONT_SIZE);
			scoreText.setString(std::string("Score ") + std::to_string(m_score));
			m_snake.render(window);
			window.draw(m_food);
			window.draw(scoreText);
			break;
		}
		case true: {
			sf::Text gameoverText;
			gameoverText.setFont(m_font);
			gameoverText.setFillColor(sf::Color::Red); // Change based on selection
			gameoverText.setString(std::string("Game Over"));
			gameoverText.setCharacterSize(TITLE_FONT_SIZE);
			gameoverText.setPosition(300*2, 250*2+50);
			window.draw(gameoverText);
			break;
		}
	}
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

	if (m_snake.hasEatenItSelf()) {
		m_isGameOver = true;
		return;
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
		m_food.setSize(sf::Vector2f(DEFAULT_SNAKE_SIZE_X, DEFAULT_SNAKE_SIZE_Y));
		m_score += 10;
		m_snake.grow();
	}

	auto currentPosition = m_snake.getHeadPosition();
	if ((currentPosition.x < 0 || (currentPosition.x + DEFAULT_SNAKE_SIZE_X) > WIDTH) ||
		(currentPosition.y < 0 || (currentPosition.y + DEFAULT_SNAKE_SIZE_Y) > HEIGHT)) {
		m_isGameOver = true;
	}
}

bool GameLoop::isGameOver() const
{
	return m_isGameOver;
}
