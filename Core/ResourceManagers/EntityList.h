#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "../Common/Entity.h"
#include "ResourceManager.h"
#include <vector>

class EntityList {
public:
	//EntityList(sol::state& lua) : _lua(lua) {}
	static Entity* loadEntity(const sol::this_state& ts, const std::string& type);

	static void update(const sf::Time& dTime);
	static void render(sf::RenderWindow*, const sf::Time& dTime);

	static Entity* getPlayer() { return _playerRef; }
	static Entity* getClosestInteractive();
	static void interactWithClosest();

	static void addEntityWithTag(Entity*, const std::string&);
	static std::vector<Entity*> getEntitiesFromTag(const std::string& tag);
private:
	static Entity* _playerRef;
	static std::vector<Entity*> _entities;

	static std::vector<Entity*> _interactiveEntities;

	static std::map<std::string, std::vector<Entity*>> _tags;
	//sol::state _lua;
	//std::vector<std::unique_ptr<Entity>> entities;
};

#endif
