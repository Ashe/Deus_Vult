#include "GameScreen.h"
#include "../Core/ResourceManagers/ResourceManager.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_lua.open_libraries();
    ResourceManager::setLua(_lua);

	lfs::loadFunctions(_lua);

	_controller.initialise(&_input);

    _map.loadMap("maps/testmap.lua");
}

bool GameScreen::update(const sf::Time& dTime) {

    EntityList::update(dTime);
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	sf::Vector2f pos = EntityList::getPlayer()->get<TransformComponent>()->_position;
	_window->setView(sf::View(pos, _window->getView().getSize()));

    _map.render(_window);

	EntityList::render(_window, dTime);
}

void GameScreen::handleEvent(const sf::Event& e) {
	_input.handleEvent(e);
}

void GameScreen::quit() {

}
