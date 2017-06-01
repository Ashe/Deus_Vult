#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include "Component.h"
#include "..\Common\Scripts.h"

#include "SFML\System.hpp"

class ScriptComponent : public Component {
public:
	ScriptComponent(Entity* e, sol::table& ComponentTable, sol::state_view& lua);

	void init();
	void update(const sf::Time&);
	void interact();

private:
	sol::state_view& _lua;
	std::string _scriptPath;

	sol::function _init;
	sol::function _update;
	sol::function _interact;
};

#endif // !SCRIPTCOMPONENT_H
