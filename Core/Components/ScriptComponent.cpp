#include "ScriptComponent.h"

#include "..\ResourceManagers\EntityList.h"

ScriptComponent::ScriptComponent(Entity* e, sol::table& ComponentTable, sol::state_view& lua) : Component(e), _lua(lua) {
	auto scriptRef = ComponentTable["script"];
	if (scriptRef.valid()) {
		_scriptPath = scriptRef;
		luah::loadScript(lua, scriptRef);

		// if there's an init function, prepare to call it after initialisation
		if (_lua["init"]) {
			_owner->addInitFunction([this]() {init(); });
		}

		// if there's an update function, call it every frame
		if (_lua["update"]) {
			_owner->addUpdateFunction([this](const sf::Time& dTime) {update(dTime); });
		}

		// if there's an interact function, call it when used
		if (_lua["interact"]) {
			_owner->addInteractFunction([this]() {interact(); });
		}
	}
	else {
		printf("Error, ScriptComponent.script is not a string!\n");
		return;
	}
}

void ScriptComponent::init() {
	_lua["this"] = _owner;
	_lua["init"]();
}

void ScriptComponent::update(const sf::Time& dTime) {
	_lua["this"] = _owner;
	_lua["dTime"] = dTime;
	_lua["update"](dTime);
}

void ScriptComponent::interact() {
	_lua["this"] = _owner;
	_lua["interact"]();
}
