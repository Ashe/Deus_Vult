#include "MovementComponent.h"
#include "../Common/Entity.h"

#include "../Common/Scripts.h"

MovementComponent::MovementComponent(Entity* e, sol::table& mcTable) : Component(e) {
	if (mcTable["maxSpeed"])
		_maxspeed = (mcTable["maxSpeed"]);

	if (mcTable["acceleration"])
		_acceleration = mcTable["acceleration"];

	_maxspeed *= _speedMod;
	_acceleration *= _speedMod;

	_transform = _owner->get<TransformComponent>();

	_graphics = _owner->get<SpineComponent>();
	if (!_graphics)
		_graphics = _owner->get<SpriteComponent>();

	// Add update function to functionlist
	_owner->addUpdateFunction([this](const sf::Time&dTime) {update(dTime); });
}

void MovementComponent::setLockMovement(bool lock) {
	_lockMovement = lock;
}

void MovementComponent::addDirection(int dir) {
	_direction += dir;
}

void MovementComponent::setSprintSpeed(int mult) {
	_speedMultiplier = mult;
}

void MovementComponent::moveToMidpoint() {
	if (!_transform || !_map) {
		_transform = _owner->get<TransformComponent>();
		_map = MapManager::getCurrentMap();
	}

	if (_transform && _map) {
		_moveToDestination = _map->getMidPointX(_transform->_position.x);
		_savedDirection=  _transform->_flipX;
		_movingToDestination = true;
	}
}

void MovementComponent::update(const sf::Time& dTime) {
	if (_transform && _graphics) {

        const float deltaT = dTime.asSeconds();

		int dirToUse = _direction;
		if (_lockMovement) {
			if (!_movingToDestination)
				return;
			else {
				const int diff = _transform->_position.x - _moveToDestination;
				if (diff != 0)
					dirToUse = (-diff) / abs(diff);
				else
					dirToUse = 0;
			}
		}

		// If the player is free to move
		switch (dirToUse) {
		case -1:
		case 1:
			_transform->_flipX = (dirToUse < 0);

			if (_speedMultiplier <= 1)
				_graphics->changeAnimation("walk");
			else
				_graphics->changeAnimation("run");

			// If moving in a direction, accelerate
			// If there's no acceleration, go at max speed
			// If there's no max speed, accelerate with no cap
			if (_acceleration > 0)
				_currentSpeed += dirToUse * _acceleration * deltaT;

			if ((_maxspeed > 0 && abs(_currentSpeed) > _maxspeed) || _acceleration <= 0)
			  _currentSpeed = dirToUse * _maxspeed;

			break;
		case 0:
			_graphics->changeAnimation("idle");

			// If 0, then you are slowing down to 0
			if (_currentSpeed != 0) {
				int mod = (_currentSpeed < 0) * 2 - 1;

				if (_acceleration > 0) {
					_currentSpeed += mod * _acceleration * deltaT;
					if (abs(_currentSpeed) < 0.01)
						_currentSpeed = 0;
				}
				else
					_currentSpeed = 0;
			}
			break;
		default:
			// If _direction is not between -1 and 1, its not valid
			printf("Direction %d is not valid!", dirToUse);
		}

		if (!_movingToDestination)
			_transform->_position.x += _currentSpeed * _speedMultiplier * deltaT;
		else {
			// If moving to a destination, check to see if it is in range
			if (abs(_moveToDestination - _transform->_position.x) > abs(_currentSpeed * _speedMultiplier * deltaT)) {
				_transform->_position.x += _currentSpeed * _speedMultiplier * deltaT;
			}
			else {
				_transform->_position.x = _moveToDestination;
				_transform->_flipX = _savedDirection;
				_movingToDestination = false;
				_currentSpeed = 0;
			}

		}

		/*if (_map)
            _map->snapToMap(_transform->_position);
        else*/
        _map = MapManager::getCurrentMap();
        _map->snapToMap(_transform->_position);

		return;
	}

	// If there's no transform component or graphics
	_transform = _owner->get<TransformComponent>();
	_graphics = _owner->get<SpineComponent>();
	if (!_graphics)
		_graphics = _owner->get<SpriteComponent>();
}
