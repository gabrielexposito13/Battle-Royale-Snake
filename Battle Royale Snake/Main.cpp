#include "GameState.hpp"
#include "Constants.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake Battle Royale");
    window.setFramerateLimit(FPS);
    GameStateLoop gameStateLoop;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gameStateLoop.processEvent(window, event);
        }
        gameStateLoop.update();
        gameStateLoop.render(window);

    }

    return 0;
}