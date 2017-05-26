#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "..\Core\EntityList.h"
#include "EntityExtra.h"

#include "..\Core\InputManager.h"

class InputManager;

class Controller {
public:
	Controller(EntityList* list) : _list(list) {}

	void initialise(InputManager* const);

private:
	EntityList* _list;
	Entity* _player;
};

#endif