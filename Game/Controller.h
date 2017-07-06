#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Core/ResourceManagers/EntityList.h"

#include "../Core/ResourceManagers/InputManager.h"

class InputManager;

class Controller {
public:
	void initialise(InputManager* const, sol::state& lua);

private:
	Entity* _player;
	MovementComponent* _movementComponent;

	sol::function _combat;

	void addDirLeft();
	void addDirRight();

	void startSprinting();
	void stopSprinting();

	void doCombat();
};

#endif