#include "EntityList.h"

Entity* EntityList::_playerRef = NULL;
std::vector<Entity*> EntityList::_entities;
std::vector<Entity*> EntityList::_interactiveEntities;
std::map<std::string, std::vector<Entity*>> EntityList::_tags;

Entity* EntityList::loadEntity(const sol::this_state& ts, const std::string& path) {
	sol::state_view _lua(ts);

	auto e = new Entity;
	//std::unique_ptr<Entity> e = std::make_unique<Entity>();

	sol::table resultTable = ResourceManager::getTable(path);
    sol::table entityTable;
    std::string entityType;
	for (auto &key_value_pair : resultTable) {
		entityType = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;

        entityTable = value.as<sol::table>();
    }

	e->setType(entityType);

	printf("-----------------------------\nLoading entity %s.\n-----------------------------\n", entityType.c_str());
	for (auto &key_value_pair : entityTable) {
		std::string componentName = key_value_pair.first.as<std::string>();
		sol::object& value = key_value_pair.second;

		printf("Adding %s to %s..\n", componentName.c_str(), entityType.c_str());

        bool successful = true;

		if (componentName == "Tags") {
			sol::table tagTable = value.as<sol::table>();
			addComponent<TagComponent>(e, tagTable);
		}
		else if (componentName == "SpriteComponent") {
			sol::table gcTable = value.as<sol::table>();
			addComponent<SpriteComponent>(e, gcTable);
		}
		else if (componentName == "SpineComponent") {
			sol::table gcTable = value.as<sol::table>();
			addComponent<SpineComponent>(e, gcTable);
		}
		else if (componentName == "SensoryComponent") {
			sol::table scTable = value.as<sol::table>();
			addComponent<SensoryComponent>(e, scTable);
		}
		else if (componentName == "InteractionComponent") {
			sol::table icTable = value.as<sol::table>();
			_interactiveEntities.push_back(e);
			addComponent<InteractionComponent>(e, icTable);
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
			sol::table mcTable = value.as<sol::table>();
			addComponent<MovementComponent>(e, mcTable);
		}
		else if (componentName == "NpcComponent") {
			sol::table npccTable = value.as<sol::table>();
			addComponent<NpcComponent>(e, npccTable);
		}
		else if (componentName == "ScriptComponent") {
			sol::table scTable = value.as<sol::table>();
			addComponent(e, scTable, _lua);
		}
		else if (componentName == "CombatComponent") {
			sol::table cbTable = value.as<sol::table>();
			addComponent<CombatComponent>(e, cbTable);
		}
        else {
            successful = false;
        }

        if (successful)
            printf("|- Loading successful.\n");
        else
            printf("|- Error: %s is not a valid component.", componentName.c_str());
	}
	printf("-----------------------------\n%s entity loaded.\n-----------------------------\n", entityType.c_str());

	//auto returnPtr = e.get();
	//entities.push_back(std::move(e));

	if (entityType != "player")
		_entities.push_back(e);
	else
		_playerRef = e;

	e->init();

	return e;
}

void EntityList::update(const sf::Time& dTime) {
    _playerRef->update(dTime);

	for (Entity* entity : _entities) {
        entity->update(dTime);
	}
}

void EntityList::render(sf::RenderWindow* window, const sf::Time& dTime) {

	for (Entity* entity : _entities) {
		entity->render(window, dTime);
	}

	_playerRef->render(window, dTime);
}

Entity* EntityList::getClosestInteractive() {
	Entity* closestEntity = nullptr;
	float distance = 999999;

	for (auto &entity : _interactiveEntities) {
		auto transform = entity->get<TransformComponent>();
		auto playerTransform = getPlayer()->get<TransformComponent>();
		auto sensoryComponent = entity->get<SensoryComponent>();

		if (sensoryComponent && transform) {
			float thisDist = abs(transform->_position.x - playerTransform->_position.x);

			// If within range and smaller than the current record, register
			if (thisDist < sensoryComponent->getRange() && thisDist < distance) {
				distance = thisDist;
				closestEntity = entity;
			}
		}
	}
	return closestEntity;
}

void EntityList::interactWithClosest() {
	Entity* entity = getClosestInteractive();
	if (entity != nullptr)
		entity->interact();
}

void EntityList::addEntityWithTag(Entity* e, const std::string& tag) {
	if (_tags.count(tag))
		_tags[tag].push_back(e);
	else
		_tags[tag] = std::vector<Entity*>{ e };
}

std::vector<Entity*> EntityList::getEntitiesFromTag(const std::string& tag) {
	if (_tags.count(tag))
		return _tags[tag];

	return std::vector<Entity*>{};
}
