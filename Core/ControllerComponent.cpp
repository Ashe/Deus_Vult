#include "ControllerComponent.h"

ControllerComponent::ControllerComponent(sol::table & componentTable) {
	// Nothing here yet
}

void ControllerComponent::addDirLeft() {
	_direction -= 1;
	printf("\tMove Left, direction: %d\n", _direction);
	assert(_direction > -2 && _direction < 2);
}

void ControllerComponent::addDirRight() {
	_direction += 1;
	printf("\tMove Right, direction: %d\n", _direction);
	assert(_direction > -2 && _direction < 2);
}
