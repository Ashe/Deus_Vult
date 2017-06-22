#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "../Core/Common/Screen.h"

#include "../Core/Common/Scripts.h"
#include "../Core/ResourceManagers/EntityList.h"
#include "../Core/ResourceManagers/InputManager.h"

#include "LuaFunctions.h"
#include "Controller.h"

#include <spine/spine-sfml.h>

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


	// TEST
	void GameScreen::hero(const char* jsonName, const char* binaryName, const char* atlasName,
		float scale);

	spine::SkeletonDrawable* _hero;
	SkeletonBounds* _bounds;
	SkeletonData* _skeletonData;
	Atlas* _atlas;
	Skeleton* _skeleton;
	Slot* _headSlot;
};

#endif
