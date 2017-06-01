#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "..\Core\Common\Screen.h"

#include "..\Core\Common\Scripts.h"
#include "..\Core\ResourceManagers\EntityList.h"
#include "..\Core\ResourceManagers\InputManager.h"

#include "LuaFunctions.h"
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

	sol::state _lua;

	Controller _controller;

	sf::Font font;
	sf::Text text;

};

#endif