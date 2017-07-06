#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../Core/Common/Screen.h"

#include "../Core/Common/Scripts.h"
#include "../Core/ResourceManagers/EntityList.h"
#include "../Core/ResourceManagers/InputManager.h"
#include "../Core/ResourceManagers/MapManager.h"

#include "LuaFunctions.h"
#include "Controller.h"

#include "../Core/HUD/HUD.h"

#include <spine/spine-sfml.h>

class GameScreen : public Screen {
public:
	GameScreen(sf::RenderWindow*);
	void init();
	void update(const sf::Time&);
	void render(const sf::Time&);
	virtual void updateWindowSize(const sf::Vector2u&);
	void handleEvent(const sf::Event&);
	void quit();

private:
	sf::RenderWindow* _window;
	InputManager _input;

	sol::state _lua;

	Controller _controller;
    GameMap* _map;
	HUD _hud;

	sf::Vector2f* _playerPos;
	sf::Vector2f getPlayerPos();
	
};

#endif
