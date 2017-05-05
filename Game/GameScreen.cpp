#include "GameScreen.h"

GameScreen::GameScreen(sf::RenderWindow* window)
	:_window(window) {}

void GameScreen::init() {
	_shape = sf::CircleShape(100.f);
	_shape.setFillColor(sf::Color::Green);

}

bool GameScreen::update(const sf::Time& dTime) {
	return false;
}

void GameScreen::render(const sf::Time& dTime) {
	_window->draw(_shape);
}

void GameScreen::quit() {

}