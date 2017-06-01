#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "..\Core\ResourceManagers\EntityList.h"

#include "..\Core\ResourceManagers\InputManager.h"

class InputManager;

class Controller {
public:
	void initialise(InputManager* const);

private:
	Entity* _player;
};

#endif