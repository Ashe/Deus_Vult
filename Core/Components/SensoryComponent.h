#ifndef SENSORYCOMPONENT_H
#define SENSORYCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include "TransformComponent.h"

class SensoryComponent : public Component {
public:
	SensoryComponent(Entity* e, sol::table& componentTable);

	sf::Vector2f getPlayerPos();

private:
	TransformComponent* _playerPosition;
};

#endif // !SENSORYCOMPONENT_H
