#include "Entity.h"
#include "Component.h"

Entity::~Entity() {
	for (auto& c : components) {
		delete c.second;
	}
}

void Entity::addComp(std::type_index type, Component* c) {
	components[type] = c;
}

Entity* Entity::loadEntity(lua_State* L, const std::string& type) {
	sol::state_view lua(L);

	auto e = new Entity();
	e->setType(type);

	auto v = luah::getTableKeys(L, type);
	//sol::table entityTable = getGlobal(L, type.c_str());
	sol::table entityTable = lua[type];

	for (auto& componentName : v) {
		if (componentName == "GraphicsComponent") {
			sol::table gcTable = entityTable["GraphicsComponent"];
			addComponent<GraphicsComponent>(e, gcTable);
		}
		else if (componentName == "NpcComponent") {
			sol::table npccTable = entityTable["NpcComponent"];
			addComponent<NpcComponent>(e, npccTable);
		}

		printf("Added %s to %s.\n", componentName.c_str(), type.c_str());
	}
	return e;
}