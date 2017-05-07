#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "..\Core\Screen.h"

#include "..\Core\Scripts.h"
#include "..\Core\EntityList.h"

class GameScreen : public Screen {
public:
	GameScreen(sf::RenderWindow*);
	void init();
	bool update(const sf::Time&);
	void render(const sf::Time&);
	void quit();

private:
	sf::RenderWindow* _window;
	EntityList entities;

	sf::CircleShape _shape;

};

#endif