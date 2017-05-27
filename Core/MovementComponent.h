#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"

#include "PositionComponent.h"
#include "GraphicsComponent.h"

#include "SFML\Graphics.hpp"

class MovementComponent : public Component {
public:
	MovementComponent(Entity* e, sol::table& componentTable);

	int _direction = 0;
	void update(const sf::Time& dTime);

private:
	PositionComponent* _position;
	float _maxspeed = 0;
	float _acceleration = 0;
	float _currentSpeed = 0;

	// Default modifier
	float _speedMod = 0.05;

	GraphicsComponent* _graphics;
};

#endif

