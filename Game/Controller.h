#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Core/ResourceManagers/EntityList.h"
#include "../Core/ResourceManagers/InputManager.h"

#include "../Core/HUD/HUD.h"

class InputManager;

class Controller {
public:
	void initialise(InputManager* const, HUD* hud);

private:
	Entity* _player;
	HUD* _hud;

	MovementComponent* _movementComponent;
	sol::table _validStats;

	void handleInput(int, bool);
	sol::function _handleInput;
};

#endif