#include "Controller.h"

void Controller::initialise( InputManager* input) {
	_player = _list->getPlayer();

	input->bindKeyToAction(sf::Keyboard::A, "moveLeft");
	input->bindKeyToAction(sf::Keyboard::D, "moveRight");

	auto temp = _player->get<ControllerComponent>();
	std::function<void()> moveLeft = std::bind(&ControllerComponent::addDirLeft, _player->get<ControllerComponent>());
	std::function<void()> moveRight = std::bind(&ControllerComponent::addDirRight, _player->get<ControllerComponent>());

	input->bindActionToFunction("moveLeft", moveLeft, moveRight);
	input->bindActionToFunction("moveRight", moveRight, moveLeft);
}