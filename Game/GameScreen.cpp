#include "GameScreen.h"
#include "../Core/ResourceManagers/ResourceManager.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_lua.open_libraries();
    ResourceManager::setLua(_lua);

	lfs::loadFunctions(_lua);
	_controller.initialise(&_input, &_hud);
	_hud.loadHUD("hud/styles.lua");

	// Execute now
	_lua.do_file("Data/common/scripts/executeNow.lua");

	_playerPos = &EntityList::getPlayer()->get<TransformComponent>()->_position;
    _map = MapManager::getCurrentMap();
}

void GameScreen::update(const sf::Time& dTime) {
    EntityList::update(dTime);
}

void GameScreen::render(const sf::Time& dTime) {

	// Render the main game
	_window->setView(sf::View(getPlayerPos(), sf::Vector2f(_window->getSize())));
    _map->render(_window);
	EntityList::render(_window, dTime);

	// Render the HUD
	_window->setView(sf::View(sf::FloatRect(sf::Vector2f(), sf::Vector2f(_window->getSize()))));
	_hud.render(_window, dTime);
}

void GameScreen::updateWindowSize(const sf::Vector2u& size) {
	_hud.setSizes(size);
}

void GameScreen::handleEvent(const sf::Event& e) {
	_input.handleEvent(e);
}

void GameScreen::quit() {

}

sf::Vector2f GameScreen::getPlayerPos()
{
	if (!_playerPos)
		_playerPos = &EntityList::getPlayer()->get<TransformComponent>()->_position;

	if (_playerPos)
		 return *_playerPos;

	return sf::Vector2f();
}
