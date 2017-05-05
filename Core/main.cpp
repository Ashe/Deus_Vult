#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
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
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				game.windowResized();
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