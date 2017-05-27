#include "ControllerComponent.h"

#include "Entity.h"

ControllerComponent::ControllerComponent(Entity* e, sol::table & componentTable) : Component(e) {
	_movementComponent = _owner->get<MovementComponent>();

}

void ControllerComponent::addDirLeft() {
	if (_movementComponent) {
		_movementComponent->_direction -= 1;
		//printf("\tMove Left,  direction: %d\n", _movementComponent->_direction);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _owner->get<MovementComponent>();
	addDirLeft();
}

void ControllerComponent::addDirRight() {
	if (_movementComponent) {
		_movementComponent->_direction += 1;
		//printf("\tMove Right, direction: %d\n", _movementComponent->_direction);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _owner->get<MovementComponent>();
	addDirRight();
}
