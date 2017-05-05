#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "..\Core\Screen.h"

class GameScreen : public Screen {
public:
	GameScreen(sf::RenderWindow*);
	void init();
	bool update(const sf::Time&);
	void render(const sf::Time&);
	void quit();

private:
	sf::RenderWindow* _window;

	sf::CircleShape _shape;

};

#endif