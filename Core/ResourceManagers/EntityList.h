#ifndef ENTITYLIST_H
#define ENTITYLIST_H

#include "..\Common\Entity.h"
#include <vector>

class EntityList {
public:
	//EntityList(sol::state& lua) : _lua(lua) {}
	Entity* loadEntity(const sol::this_state& ts, const std::string& type);

	void update(const sf::Time& dTime);
	void render(sf::RenderWindow*, const sf::Time& dTime);

	static Entity* getPlayer() { return _playerRef; }
private:
	static Entity* _playerRef;
	std::vector<Entity*> entities;
	//sol::state _lua;
	//std::vector<std::unique_ptr<Entity>> entities;
};

#endif