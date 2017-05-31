#include "EntityList.h"

Entity* EntityList::_playerRef = NULL;

Entity* EntityList::loadEntity(const sol::this_state& ts, const std::string& type) {
	sol::state_view _lua(ts);

	auto e = new Entity;
	//std::unique_ptr<Entity> e = std::make_unique<Entity>();
	e->setType(type);

	sol::table entityTable = _lua[type];

	printf("-----------------------------\nLoading entity %s.\n-----------------------------\n", type.c_str());
	for (auto key_value_pair : entityTable) {
		std::string componentName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;

		if (componentName == "GraphicsComponent") {
			sol::table gcTable = value.as<sol::table>();
			addComponent<GraphicsComponent>(e, gcTable);
		}
		else if (componentName == "SensoryComponent") {
			sol::table scTable = value.as<sol::table>();
			addComponent<SensoryComponent>(e, scTable);
		}
		else if (componentName == "OutlineComponent") {
			sol::table pcTable = value.as<sol::table>();
			addComponent<OutlineComponent>(e, pcTable);
		}
		else if (componentName == "TransformComponent") {
			sol::table pcTable = value.as<sol::table>();
			addComponent<TransformComponent>(e, pcTable);
		}
		else if (componentName == "MovementComponent") {
			sol::table pcTable = value.as<sol::table>();
			addComponent<MovementComponent>(e, pcTable);
		}
		else if (componentName == "NpcComponent") {
			sol::table npccTable = value.as<sol::table>();
			addComponent<NpcComponent>(e, npccTable);
		}
		else if (componentName == "ControllerComponent") {
			sol::table ccTable = value.as<sol::table>();
			addComponent<ControllerComponent>(e, ccTable);
		}
		printf("Added %s to %s.\n", componentName.c_str(), type.c_str());
	}
	printf("-----------------------------\n%s entity loaded.\n-----------------------------\n", type.c_str());

	//auto returnPtr = e.get();
	//entities.push_back(std::move(e));

	if (type != "player")
		entities.push_back(e);
	else
		_playerRef = e;

	return e;
}

void EntityList::update(const sf::Time& dTime) {
	_playerRef->update(dTime);

	for (Entity* entity : entities) {
		entity->update(dTime);
	}
}

void EntityList::render(sf::RenderWindow* window, const sf::Time& dTime) {
	for (Entity* entity : entities) {
		entity->render(window, dTime);
	}

	_playerRef->render(window, dTime);
}