#include "Game.h"
#include "cmath"

Game::Game(sf::RenderWindow* window)
	:_window(window), _game(window) {}

void Game::init() {
	// Set up the view
	windowResized();

	// Set the game as the thing to display
	_currentScreen = &_game;
	_currentScreen->init();
}

void Game::windowResized() {
        // This function is called whenever the window is resized
        int tempX = std::round(_window->getSize().x);
        int tempY = std::round(_window->getSize().y);

	tempX = (tempX % 2 == 0) ? tempX : tempX + 1;
	tempY = (tempY % 2 == 0) ? tempY : tempY + 1;

	_window->setSize(sf::Vector2u(tempX, tempY));
	_view = sf::View(sf::FloatRect(0, 0, _window->getSize().x, _window->getSize().y));
	_window->setView(_view);
}

bool Game::update(const sf::Time& dTime) {
	return _currentScreen->update(dTime);
}

void Game::render(const sf::Time& dTime) {
	_currentScreen->render(dTime);
}

void Game::handleEvent(const sf::Event& e) {
	_currentScreen->handleEvent(e);
}

void Game::quit() {
	_game.quit();
}
