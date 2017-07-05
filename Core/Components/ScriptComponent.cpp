#include "ScriptComponent.h"

#include "../ResourceManagers/EntityList.h"

ScriptComponent::ScriptComponent(Entity* e, sol::table& ComponentTable, sol::state_view& lua) : Component(e), _lua(lua) {
	auto scriptRef = ComponentTable["script"];
	if (scriptRef.valid()) {
		_scriptPath = scriptRef;
		sol::table table = lua.do_file("Data/" + _scriptPath);
		//sol::table table = ResourceManager::getTable(_scriptPath);

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

		// if there's a function for interaction, add it to list
		if (table["interact"]) {
			_interact = table["interact"];
			_owner->addInteractFunction([this]() {interact(); });
		}

		// if there's a function for the player entering range, register
		if (table["inRange"]) {
			_inRange = table["inRange"];
		}

		// if there's a function for leaving range, register
		if (table["outRange"]) {
			_outRange = table["outRange"];
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

void ScriptComponent::inRange() {
    if (_inRange)
        _inRange(_owner);
}

void ScriptComponent::outRange() {
    if (_outRange)
        _outRange(_owner);
}
