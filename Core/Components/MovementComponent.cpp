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

void MovementComponent::update(const sf::Time& dTime) {
	if (_transform && _graphics) {

        const float deltaT = dTime.asSeconds();

		switch (_direction) {
		case -1:
		case 1:
			_transform->_flipX = (_direction < 0);

			if (_speedMultiplier <= 1)
				_graphics->changeAnimation("walk");
			else
				_graphics->changeAnimation("run");

			// If moving in a direction, accelerate
			// If there's no acceleration, go at max speed
			// If there's no max speed, accelerate with no cap
			if (_acceleration > 0)
                _currentSpeed += _direction * _acceleration * deltaT;

			if ((_maxspeed > 0 && abs(_currentSpeed) > _maxspeed) || _acceleration <= 0)
              _currentSpeed = _direction * _maxspeed;

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
			printf("Direction %d is not valid!", _direction);
		}

		_transform->_position.x += _currentSpeed * _speedMultiplier * deltaT;

		if (_map)
			_map->snapToMap(_transform->_position);
		else 
			_map = MapManager::getCurrentMap();

		return;
	}

	// If there's no transform component or graphics
	_transform = _owner->get<TransformComponent>();
	_graphics = _owner->get<SpineComponent>();
	if (!_graphics)
		_graphics = _owner->get<SpriteComponent>();;
}
