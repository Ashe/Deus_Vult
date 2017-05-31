#ifndef INTERACTIONCOMPONENT_H
#define INTERACTIONCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include "SFML\Graphics.hpp"

class InteractionComponent : public Component {
public:
	InteractionComponent(Entity* e, sol::table& componentTable);

	void render(sf::RenderWindow*, const sf::Time&);
private:
};

#endif // !INTERACTIONCOMPONENT_H
