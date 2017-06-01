#include "GameScreen.h"
#include "../Core/ResourceManagers/ResourceManager.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	sol::state lua;
	lua.open_libraries();

	lfs::loadFunctions(lua);

	_controller.initialise(&_input);
}

bool GameScreen::update(const sf::Time& dTime) {

	EntityList::update(dTime);
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	sf::Vector2f pos = EntityList::getPlayer()->get<TransformComponent>()->_position;
	_window->setView(sf::View(pos, _window->getView().getSize()));

	EntityList:: render(_window, dTime);

	_window->draw(text);
}

void GameScreen::handleEvent(const sf::Event& e) {
	_input.handleEvent(e);
}

void GameScreen::quit() {

}

