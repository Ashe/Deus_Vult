#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <string>
#include "../Common/Scripts.h"
#include "Component.h"

#include "TransformComponent.h"
#include "GraphicsComponentBase.h"

#include "../ResourceManagers/MapManager.h"

#include <SFML/Graphics.hpp>

class MovementComponent : public Component {
public:
	MovementComponent(Entity* e, sol::table& componentTable);

	int _direction = 0;
	float _speedMultiplier = 1;

	void update(const sf::Time& dTime);

private:
	TransformComponent* _transform;
	GraphicsComponentBase* _graphics;
	GameMap* _map;

	float _maxspeed = 0;
	float _acceleration = 0;
	float _currentSpeed = 0;

	// Default modifier
	float _speedMod = 0.05;
};

#endif

