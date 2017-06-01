#include "ScriptComponent.h"

#include "..\ResourceManagers\EntityList.h"

ScriptComponent::ScriptComponent(Entity* e, sol::table& ComponentTable, sol::state_view& lua) : Component(e), _lua(lua) {
	auto scriptRef = ComponentTable["script"];
	if (scriptRef.valid()) {
		_scriptPath = scriptRef;
		//luah::loadScript(lua, scriptRef);
		sol::table table = lua.do_file("Data/" + _scriptPath);

		// if there's an init function, prepare to call it after initialisation
		if (table["init"]) {
			_init = table["init"];
			_owner->addInitFunction([this]() {init(); });
		}

		// if there's an update function, call it every frame
		if (table["update"]) {
			_update = table["update"];
			_owner->addUpdateFunction([this](const sf::Time& dTime) {update(dTime); });
		}

		// if there's an interact function, call it when used
		if (table["interact"]) {
			_interact = table["interact"];
			_owner->addInteractFunction([this]() {interact(); });
		}
	}
	else {
		printf("Error, ScriptComponent.script is not a string!\n");
		return;
	}
}

void ScriptComponent::init() {
	_init(_owner);
}

void ScriptComponent::update(const sf::Time& dTime) {
	_update(_owner, dTime);
}

void ScriptComponent::interact() {
	_interact(_owner);
}
