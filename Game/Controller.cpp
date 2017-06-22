#include "Controller.h"

void Controller::initialise( InputManager* input) {
	_player = EntityList::getPlayer();

	input->bindKeyToAction(sf::Keyboard::A, "moveLeft");
	input->bindKeyToAction(sf::Keyboard::D, "moveRight");
	input->bindKeyToAction(sf::Keyboard::E, "interact");
	input->bindKeyToAction(sf::Keyboard::LShift, "sprint");

	input->bindKeyToAction(sf::Keyboard::Space, "test");

	auto temp = _player->get<ControllerComponent>();
	std::function<void()> moveLeft = std::bind(&ControllerComponent::addDirLeft, _player->get<ControllerComponent>());
	std::function<void()> moveRight = std::bind(&ControllerComponent::addDirRight, _player->get<ControllerComponent>());
	std::function<void()> interact = std::bind(&EntityList::interactWithClosest);
	std::function<void()> startSprint = std::bind(&ControllerComponent::startSprinting, _player->get<ControllerComponent>());
	std::function<void()> stopSprint = std::bind(&ControllerComponent::stopSprinting, _player->get<ControllerComponent>());

	std::function<void()> test = std::bind(&ControllerComponent::test, _player->get<ControllerComponent>());

	input->bindActionToFunction("moveLeft", moveLeft, moveRight);
	input->bindActionToFunction("moveRight", moveRight, moveLeft);
	input->bindActionToFunction("interact", interact, NULL);
	input->bindActionToFunction("sprint", startSprint, stopSprint);

	input->bindActionToFunction("test", test, NULL);
}