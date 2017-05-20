#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "Entity.h"
#include <vector>

class EntityList {
public:
	//EntityList(sol::state& lua) : _lua(lua) {}
	Entity* loadEntity(const sol::this_state& ts, const std::string& type);
	void render(sf::RenderWindow*, const sf::Time& dTime);
private:
	//sol::state _lua;
	//std::vector<std::unique_ptr<Entity>> entities;

	std::vector<Entity*> entities;
	bool test = false;
};

#endif