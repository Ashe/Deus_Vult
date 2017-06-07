#ifndef GAME_H
#define GAME_H

#include "../../Game/GameScreen.h"

class Game {
public:
	Game(sf::RenderWindow*);

	void init();
	bool update(const sf::Time&);
	void render(const sf::Time&);
	void handleEvent(const sf::Event&);

	void windowResized();
	void quit();

private:
	sf::RenderWindow* _window;
	sf::View _view;

	GameScreen _game;
	Screen* _currentScreen;
};

#endif