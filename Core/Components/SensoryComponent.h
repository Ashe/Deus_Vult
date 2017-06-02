#ifndef SENSORYCOMPONENT_H
#define SENSORYCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include "TransformComponent.h"
#include "ScriptComponent.h"

class SensoryComponent : public Component {
public:
	SensoryComponent(Entity* e, sol::table& componentTable);

	void update(const sf::Time& dTime);

	sf::Vector2f getPlayerPos();
	bool playerInRange();

	float getRange() { return _range; }

private:
	TransformComponent* _playerTransform;
	TransformComponent* _ownerTransform;

	sf::Vector2f _playerPosition;

	float _range;
	bool _inRange;

	ScriptComponent* _scripts;
};

#endif // !SENSORYCOMPONENT_H
