#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "../Common/Entity.h"
#include <vector>

static class EntityList {
public:
	//EntityList(sol::state& lua) : _lua(lua) {}
	static Entity* loadEntity(const sol::this_state& ts, const std::string& type);

	static void update(const sf::Time& dTime);
	static void render(sf::RenderWindow*, const sf::Time& dTime);

	static Entity* getPlayer() { return _playerRef; }
	static Entity* getClosestInteractive();
	static void interactWithClosest();
private:
	static Entity* _playerRef;
	static std::vector<Entity*> _entities;

	static std::vector<Entity*> _interactiveEntities;
	//sol::state _lua;
	//std::vector<std::unique_ptr<Entity>> entities;
};

#endif
