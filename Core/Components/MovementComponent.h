#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h"
#include "Component.h"

#include "TransformComponent.h"
#include "GraphicsComponent.h"

#include <SFML\Graphics.hpp>

class MovementComponent : public Component {
public:
	MovementComponent(Entity* e, sol::table& componentTable);

	int _direction = 0;
	void update(const sf::Time& dTime);

private:
	TransformComponent* _transform;
	GraphicsComponent* _graphics;
	float _maxspeed = 0;
	float _acceleration = 0;
	float _currentSpeed = 0;

	// Default modifier
	float _speedMod = 0.05;
};

#endif

