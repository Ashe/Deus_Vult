#include "GameScreen.h"
#include "../Core/ResourceManagers/ResourceManager.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	sol::state lua;
	lua.open_libraries();

	lua.set_function("loadEntity", &EntityList::loadEntity);
	luah::loadScript(lua, "player.lua");
	luah::loadScript(lua, "bruh.lua");

	luah::loadScript(lua, "makePlayer.lua");

	_controller.initialise(&_input);


	text.setFont(*ResourceManager::getFont("Data/common/fonts/belgrano/regular.ttf"));
	text.setString("Fuck bitches, get money.");
	text.setPosition(115, 155);

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

