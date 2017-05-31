#include "Controller.h"

void Controller::initialise( InputManager* input) {
	_player = EntityList::getPlayer();

	input->bindKeyToAction(sf::Keyboard::A, "moveLeft");
	input->bindKeyToAction(sf::Keyboard::D, "moveRight");
	input->bindKeyToAction(sf::Keyboard::E, "interact");

	auto temp = _player->get<ControllerComponent>();
	std::function<void()> moveLeft = std::bind(&ControllerComponent::addDirLeft, _player->get<ControllerComponent>());
	std::function<void()> moveRight = std::bind(&ControllerComponent::addDirRight, _player->get<ControllerComponent>());
	std::function<void()> interact = std::bind(&EntityList::interactWithClosest);

	input->bindActionToFunction("moveLeft", moveLeft, moveRight);
	input->bindActionToFunction("moveRight", moveRight, moveLeft);
	input->bindActionToFunction("interact", interact, NULL);
}