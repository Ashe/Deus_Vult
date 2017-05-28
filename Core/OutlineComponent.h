#ifndef OUTLINECOMPONENT_H
#define OUTLINECOMPONENT_H

#include <string>
#include "Scripts.h" 
#include "Component.h"

#include "SFML\Graphics.hpp"
#include "TransformComponent.h"

class OutlineComponent : public Component {
public:
	OutlineComponent(Entity* e, sol::table& componentTable);

	sf::Color _colour;

	float _distanceStrong;
	float _distanceWeak;

	float _thickness;

	sf::Color getOutlineColour();

private:
	TransformComponent* _playerPosition;
	TransformComponent* _thisPosition;
};

#endif 