#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "One Rider from Light's Gaze");
	Game game(&window);
	game.init();

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::KeyPressed:
			case sf::Event::KeyReleased:
			case sf::Event::MouseButtonPressed:
			case sf::Event::MouseButtonReleased:
				game.handleEvent(event);
				break;
			case sf::Event::Resized:
				game.windowResized();
				break;
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (game.update(elapsed))
			window.close();

		window.clear();
		game.render(elapsed);
		window.display();
	}

	return 0;
}
