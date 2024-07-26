#include "Menu.hpp"

void Menu::render(sf::RenderWindow& window)
{

	sf::Text titleText;
	titleText.setFont(m_font);
	titleText.setPosition(110, 150);
	titleText.setCharacterSize(50);
	titleText.setFillColor(sf::Color::Green); // Change based on selection
	titleText.setString("Snake with Battle Royale");

	sf::Text singlePlayerText;
	singlePlayerText.setFont(m_font);
	singlePlayerText.setPosition(300, 250);

	switch (m_options) {
		case MenuOptions::SinglePlayer: {
			auto singlePlayerColor = sf::Color::Magenta;
			singlePlayerText.setFillColor(singlePlayerColor); // Change based on selection
			break;
		}
		case MenuOptions::BattleRoyal: {
			auto singlePlayerColor = sf::Color::Cyan;
			singlePlayerText.setFillColor(singlePlayerColor); // Change based on selection
			break;
		}
		default:
			break;
	}

	singlePlayerText.setString("Single Player");

	auto multiplayerColor = sf::Color::Magenta;
	switch (m_options) {
	case MenuOptions::BattleRoyal: {
		multiplayerColor = sf::Color::Magenta;
		break;
	}
	case MenuOptions::SinglePlayer: {
		multiplayerColor = sf::Color::Cyan;
		break;
	}
	default:
		break;
	}
	sf::Text multiplayerText;
	multiplayerText.setFont(m_font);
	multiplayerText.setPosition(255, 300);
	multiplayerText.setFillColor(multiplayerColor);
	multiplayerText.setString("Battle Royale Mode ");

	window.draw(titleText);
	window.draw(singlePlayerText);
	window.draw(multiplayerText);
}

void Menu::processEvent(sf::RenderWindow& window, sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_options = static_cast<MenuOptions>(((static_cast<uint8_t>(m_options)) + 1) % 2);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_options = static_cast<MenuOptions>(((static_cast<int8_t>(m_options)) - 1) % 2);
	}
}
