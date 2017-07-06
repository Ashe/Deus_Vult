#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Core/ResourceManagers/EntityList.h"
#include "../Core/ResourceManagers/InputManager.h"

#include "../Core/HUD/HUD.h"

class InputManager;

class Controller {
public:
	void initialise(InputManager* const, HUD* hud, sol::state& lua);

private:
	Entity* _player;
	HUD* _hud;

	MovementComponent* _movementComponent;
	sol::table _validStats;

	sol::function _combat;

	void addDirLeft();
	void addDirRight();

	void startSprinting();
	void stopSprinting();

	void doCombat();
};

#endif