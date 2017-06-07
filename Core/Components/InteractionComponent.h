#ifndef INTERACTIONCOMPONENT_H
#define INTERACTIONCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include <SFML/Graphics.hpp>
#include "..\ResourceManagers\ResourceManager.h"

#include "TransformComponent.h"
#include "SensoryComponent.h"

class InteractionComponent : public Component {
public:
	InteractionComponent(Entity* e, sol::table& componentTable);

	void render(sf::RenderWindow*, const sf::Time&);
private:
	sf::Text _text;

	TransformComponent* _transform;
	SensoryComponent* _sensor;
	float _spriteHeight;
};

#endif // !INTERACTIONCOMPONENT_H
