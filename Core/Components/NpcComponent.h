#ifndef NPCCOMPONENT_H
#define NPCCOMPONENT_H

#include <string>
#include "..\Common\Scripts.h" 
#include "Component.h"

class NpcComponent : public Component {
public:
	NpcComponent(Entity* e, sol::table& componentTable);

	void setPhrase(const std::string& phrase) {
		this->_phrase = phrase;
	}

	std::string getPhrase() const {
		return _phrase;
	}
private:
	std::string _phrase;
};

#endif 