#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "Entity.h"
#include <vector>

class EntityList {
public:
	//EntityList(sol::state& lua) : _lua(lua) {}
	Entity* loadEntity(const sol::this_state& ts, const std::string& type);
	void render(sf::RenderWindow*, const sf::Time& dTime);

	Entity* getPlayer() const;
private:
	std::vector<Entity*> entities;
	//sol::state _lua;
	//std::vector<std::unique_ptr<Entity>> entities;

	bool test = false;
};

#endif