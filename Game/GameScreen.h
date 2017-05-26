#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "..\Core\Screen.h"

#include "..\Core\Scripts.h"
#include "..\Core\EntityList.h"
#include "..\Core\InputManager.h"

#include "Controller.h"

class GameScreen : public Screen {
public:
	GameScreen(sf::RenderWindow*);
	void init();
	bool update(const sf::Time&);
	void render(const sf::Time&);
	void handleEvent(const sf::Event&);
	void quit();

private:
	sf::RenderWindow* _window;
	InputManager _input;

	EntityList _entities;
	Controller _controller = Controller(&_entities);

};

#endif