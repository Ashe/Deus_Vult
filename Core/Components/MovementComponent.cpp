#include "MovementComponent.h"
#include "..\Common\Entity.h"

#include <sol.hpp>

MovementComponent::MovementComponent(Entity* e, sol::table& mcTable) : Component(e) {
	if (mcTable["maxspeed"])
		_maxspeed = (mcTable["maxspeed"]);

	if (mcTable["acceleration"])
		_acceleration = mcTable["acceleration"];

	_maxspeed *= _speedMod;
	_acceleration *= _speedMod;

	_transform = _owner->get<TransformComponent>();
	_graphics = _owner->get<GraphicsComponent>();
}

void MovementComponent::update(const sf::Time& dTime) {
	if (_transform) {
		switch (_direction) {
		case -1:
		case 1:
			_transform->_flipX = (_direction < 0);

			_graphics->changeAnimation("walk");

			// If moving in a direction, accelerate
			// If there's no acceleration, go at max speed
			// If there's no max speed, accelerate with no cap
			if (_acceleration > 0)
				_currentSpeed += _direction * dTime.asSeconds() * _acceleration;

			if ((_maxspeed > 0 && abs(_currentSpeed) > _maxspeed) || _acceleration <= 0)
				_currentSpeed = _direction * _maxspeed;

			break;
		case 0:
			_graphics->changeAnimation("idle");

			// If 0, then you are slowing down to 0
			if (_currentSpeed != 0) {
				int mod = (_currentSpeed < 0) * 2 - 1;

				if (_acceleration > 0) {
					_currentSpeed += mod * _acceleration * dTime.asSeconds();
					if (abs(_currentSpeed) < 0.01)
						_currentSpeed = 0;
				}
				else
					_currentSpeed = 0;
			}
			break;
		default:
			// If _direction is not between -1 and 1, its not valid
			printf("Direction %d is not valid!", _direction);
		}

		_transform->_position.x += _currentSpeed;
		return;
	}

	// If there's no position component or graphics
	_transform = _owner->get<TransformComponent>();
	_graphics = _owner->get<GraphicsComponent>();
}