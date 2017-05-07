#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_shape = sf::CircleShape(100.f);
	_shape.setFillColor(sf::Color::Green);

	sol::state lua;
	lua.open_libraries();

	lua.set_function("loadEntity",&EntityList::loadEntity, entities);
	luah::loadScript(lua, "Data/ghost.lua");

	luah::loadScript(lua, "Data/makeGhost.lua");

	Entity* e = lua["obj"];

	auto npcc = e->get<NpcComponent>();
	printf("%s says: %s\n", e->getType().c_str(), npcc->getPhrase().c_str());
}

bool GameScreen::update(const sf::Time& dTime) {
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	_window->draw(_shape);
}

void GameScreen::quit() {

}