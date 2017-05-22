#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <string>
#include "Scripts.h"
#include "Component.h"

#include "SFML\Graphics.hpp"

class PositionComponent : public Component {
public:
	PositionComponent(sol::table& componentTable);

	sf::Vector2f _position;

};

#endif

