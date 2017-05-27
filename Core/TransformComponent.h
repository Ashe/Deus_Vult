#ifndef TRANSFORMCOMPONENT_H 
#define TRANSFORMCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"

#include "SFML\Graphics.hpp"

class TransformComponent : public Component {
public:
	TransformComponent(Entity* e, sol::table& componentTable);

	sf::Vector2f _position;
	sf::Vector2f _scale;
	float _rotation;

	bool _flipX = false;
	bool _flipY = false;

};

#endif

