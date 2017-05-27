#include "MovementComponent.h"
#include "Entity.h"

#include <sol.hpp>

MovementComponent::MovementComponent(Entity* e, sol::table& mcTable) : Component(e) {
	if (mcTable["maxspeed"])
		_maxspeed = (mcTable["maxspeed"]);

	if (mcTable["acceleration"])
		_acceleration = mcTable["acceleration"];

	_maxspeed *= _speedMod;
	_acceleration *= _speedMod;

	_position = _owner->get<PositionComponent>();
}

void MovementComponent::update(const sf::Time& dTime) {
	if (_position) {
		switch (_direction) {
		case -1:
		case 1:
			// If moving in a direction, accelerate
			// If there's no acceleration, go at max speed
			// If there's no max speed, accelerate with no cap
			if (_acceleration > 0)
				_currentSpeed += _direction * dTime.asSeconds() * _acceleration;

			if ((_maxspeed > 0 && abs(_currentSpeed) > _maxspeed) || _acceleration <= 0)
				_currentSpeed = _direction * _maxspeed;

			break;
		case 0:
			// If 0, then you are slowing down to 0
			if (_currentSpeed != 0) {
				int mod = (_currentSpeed < 0) * 2 - 1;

				if (_acceleration > 0)
					_currentSpeed += mod * _acceleration * dTime.asSeconds();
				else
					_currentSpeed = 0;
			}
			break;
		default:
			// If _direction is not between -1 and 1, its not valid
			printf("Direction %d is not valid!", _direction);
		}

		_position->_position.x += _currentSpeed;
		return;
	}

	// If there's no position component
	_position = _owner->get<PositionComponent>();
}