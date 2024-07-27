#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Menu.hpp"
#include "GameLoop.hpp"


class GameStateLoop
{
public:
	GameStateLoop() = default;
	~GameStateLoop() = default;
	void render(sf::RenderWindow& window);
	void processEvent(sf::RenderWindow& window, sf::Event& event);
	void update();
private:
	uint16_t m_gameOverTicks = 0u;
	enum GameState {
		OnMenu,
		InGame,
	};
	GameState m_gameState = GameState::OnMenu;
	std::unique_ptr<GameLoop> m_gameLoop;
	Menu m_menu;
	void renderOnMenu(sf::RenderWindow& window);
	void processEventOnMenu(sf::RenderWindow& window, sf::Event& event);
};

#endif