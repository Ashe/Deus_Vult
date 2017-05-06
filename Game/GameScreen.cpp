#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_shape = sf::CircleShape(100.f);
	_shape.setFillColor(sf::Color::Green);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luah::loadScript(L, "Data/ghost.lua");
	luah::loadGetKeysFunction(L);

	auto e = Entity::loadEntity(L, "ghost");
	auto npcc = e->get<NpcComponent>();
	printf("%s says: %s", e->getType().c_str(), npcc->getPhrase().c_str());

	lua_close(L);

}

bool GameScreen::update(const sf::Time& dTime) {
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	_window->draw(_shape);
}

void GameScreen::quit() {

}