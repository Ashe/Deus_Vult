#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h"
#include "Component.h"

#include "MovementComponent.h"

class ControllerComponent : public Component {
public:
	ControllerComponent(Entity* e, sol::table& componentTable);

	MovementComponent* _movementComponent;

	void addDirLeft();
	void addDirRight();
};

#endif

