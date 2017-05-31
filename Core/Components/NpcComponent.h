#ifndef NPCCOMPONENT_H
#define NPCCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

#include "SFML\Graphics.hpp"
#include "SensoryComponent.h"
#include "TransformComponent.h"

class NpcComponent : public Component {
public:
	NpcComponent(Entity* e, sol::table& componentTable);

	void setPhrase(const std::string& phrase) {
		this->_phrase = phrase;
	}

	std::string getPhrase() const {
		return _phrase;
	}

	void update(const sf::Time&);

	void setFacePlayer(bool);
private:

	std::string _phrase;
	bool _facePlayer;

	SensoryComponent* _sensoryComponent;
	TransformComponent* _transform;

};

#endif 