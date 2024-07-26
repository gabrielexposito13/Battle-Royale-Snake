#include "GameState.hpp"

void GameStateLoop::render(sf::RenderWindow& window)
{
	switch (this->m_gameState) {
		case GameState::OnMenu: {
			renderOnMenu(window);
			break;
		}
		case GameState::InGame: {
			m_gameLoop->render(window);
			break;
		}
	}
}

void GameStateLoop::processEvent(sf::RenderWindow& window, sf::Event& event)
{
	switch (this->m_gameState) {
		case GameState::OnMenu: {
			processEventOnMenu(window, event);
			break;
		}
		case GameState::InGame: {
			m_gameLoop->processEvent(window, event);
			break;
		}
	}
}

void GameStateLoop::update()
{
	switch (this->m_gameState) {
		case GameState::OnMenu: {
			break;
		}
		case GameState::InGame: {
			m_gameLoop->moveSnake();
			break;
		}
	}
}

void GameStateLoop::renderOnMenu(sf::RenderWindow& window)
{
	window.clear();
	m_menu.render(window);
	window.display();
}

void GameStateLoop::processEventOnMenu(sf::RenderWindow& window, sf::Event& event)
{
	if (event.type == sf::Event::Closed)
		window.close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_gameState == GameState::OnMenu) {
		m_gameLoop = std::make_unique<GameLoop>(GameLoop(m_menu.m_options == Menu::MenuOptions::BattleRoyal));
		m_gameState = GameState::InGame;
	}
	m_menu.processEvent(window, event);
}
