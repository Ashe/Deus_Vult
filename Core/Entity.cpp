#include "Entity.h"
#include "Component.h"

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Entity Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Entity::~Entity() {
	for (auto& c : components) {
		delete c.second;
	}
}

void Entity::addComp(std::type_index type, Component* c) {
	components[type] = c;
}

Entity* Entity::loadEntity(const sol::state& lua, const std::string& type) {

	auto e = new Entity;
	e->setType(type);

	sol::table entityTable = lua[type];

	for (auto key_value_pair : entityTable) {
		std::string componentName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;
		if (componentName == "GraphicsComponent") {
			sol::table gcTable = value.as<sol::table>();
			addComponent<GraphicsComponent>(e, gcTable);
		}
		else if (componentName == "NpcComponent") {
			sol::table npccTable = value.as<sol::table>();
			addComponent<NpcComponent>(e, npccTable);
		}

		printf("Added %s to %s.\n", componentName.c_str(), type.c_str());
	}
	return e;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LuaHandle Functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void LuaEntityHandle::setPhrase(const std::string& phrase) {
	auto npcc = e->get<NpcComponent>();
	if (npcc) {
		npcc->setPhrase(phrase);
	}
	else {
		printf("No NPC Component on entity: %s\n", e->getType().c_str());
	}
}

void LuaEntityHandle::printPhrase() {
	auto npcc = e->get<NpcComponent>();
	if (npcc) {
		printf("%s says: %s", e->getType().c_str(), npcc->getPhrase().c_str());
	}
	else {
		printf("No NPC Component on entity: %s\n", e->getType().c_str());
	}
}