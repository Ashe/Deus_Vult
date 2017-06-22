#include "ControllerComponent.h"

#include "../Common/Entity.h"

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
	//printf("No MovementComponent found on moveLeft. Trying again..\n");
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
	//printf("No MovementComponent found on moveRight. Trying again..\n");
	//addDirRight();
}

void ControllerComponent::startSprinting() {
	if (_movementComponent) {
		_movementComponent->_speedMultiplier = 2;
		//printf("\tStart Sprint, multiplier: %d\n", _movementComponent->_speedMultiplier);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _owner->get<MovementComponent>();
	_movementComponent->_speedMultiplier = 2;
	//printf("No MovementComponent found on startSprinting. Trying again..\n");
}

void ControllerComponent::stopSprinting() {
	if (_movementComponent) {
		_movementComponent->_speedMultiplier = 1;
		//printf("\tStop Sprint, multiplier: %d\n", _movementComponent->_speedMultiplier);
		return;
	}

	// If there's no movementComponent, try again
	_movementComponent = _owner->get<MovementComponent>();
	_movementComponent->_speedMultiplier = 1;
	//printf("No MovementComponent found on stopSprinting. Trying again..\n");
}

void ControllerComponent::test() {
	auto ref = _owner->get<SpineComponent>();
	if (ref)
		ref->playAnimation("attack", 0.5);
}
