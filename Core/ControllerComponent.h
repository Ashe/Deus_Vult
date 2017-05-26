#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"

class ControllerComponent : public Component {
public:
	ControllerComponent(sol::table& componentTable);

	int _direction = 0;

	void addDirLeft();
	void addDirRight();
};

#endif

