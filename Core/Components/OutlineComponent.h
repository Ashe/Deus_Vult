#ifndef OUTLINECOMPONENT_H
#define OUTLINECOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include <SFML\Graphics.hpp>
#include "TransformComponent.h"
#include "SensoryComponent.h"

class OutlineComponent : public Component {
public:
	OutlineComponent(Entity* e, sol::table& componentTable);

	sf::Color _colour;

	float _distanceStrong;
	float _distanceWeak;

	float _thickness;

	sf::Color getOutlineColour();

private:
	SensoryComponent* _sensor;
	TransformComponent* _thisPosition;
};

#endif 