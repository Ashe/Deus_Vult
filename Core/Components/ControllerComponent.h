#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include <string>
#include "../Common/Scripts.h"
#include "Component.h"

#include "MovementComponent.h"
#include "CombatComponent.h"
#include "SpineComponent.h"

class ControllerComponent : public Component {
public:
	ControllerComponent(Entity* e, sol::table& componentTable);

	void addDirLeft();
	void addDirRight();

	void startSprinting();
	void stopSprinting();
private:
	MovementComponent* _movementComponent;
};

#endif

