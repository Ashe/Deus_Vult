#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	sol::state lua;
	lua.open_libraries();

	lua.set_function("loadEntity",&EntityList::loadEntity, &_entities);
	luah::loadScript(lua, "knight.lua");

	luah::loadScript(lua, "makeKnight.lua");
	Entity* e = lua["obj"];

	auto npcc = e->get<NpcComponent>();
	printf("%s says: %s\n", e->getType().c_str(), npcc->getPhrase().c_str());

	_input.loadGameControls();
}

bool GameScreen::update(const sf::Time& dTime) {
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	_entities.render(_window, dTime);
}

void GameScreen::handleEvent(const sf::Event& e) {
	_input.handleEvent(e);
}

void GameScreen::quit() {

}

