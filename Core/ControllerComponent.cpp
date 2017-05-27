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
	_movementComponent->_direction -= 1;
	printf("No MovementComponent found on moveLeft. Trying again..\n");
	//addDirLeft();
}

void ControllerComponent::addDirRight() {
	if (_movementComponent) {
		_movementComponent->_direction += 1;
		//printf("\tMove Right, direction: %d\n", _movementComponent->_direction);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _owner->get<MovementComponent>();
	_movementComponent->_direction += 1;
	printf("No MovementComponent found on moveRight. Trying again..\n");
	//addDirRight();
}
